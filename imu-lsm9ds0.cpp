#include "imu-lsm9ds0.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <chrono>

#ifdef ZMQ_ENABLE
#include <zmq.hpp>
#include <string.h>
#endif

using namespace std;

static int fd;

void writeByte(uint8_t reg, uint8_t val) {
    if (i2c_smbus_write_byte_data(fd, reg, val)) {
        perror("failed to write byte");
        exit(1);
    }
}

void writeWord(uint8_t reg, uint16_t val) {
    if (i2c_smbus_write_word_data(fd, reg, val)) {
        perror("failed to write word");
        exit(1);
    }
}

void writeBlock(uint8_t reg, uint8_t len, uint8_t * val) {
    if (i2c_smbus_write_block_data(fd, reg, len, val)) {
        perror("failed to write block");
        exit(1);
    }
}

uint8_t readByte(uint8_t reg) {
    return i2c_smbus_read_byte_data(fd, reg);
}

uint32_t readBlock(uint8_t reg) {
    uint32_t res = 0;
    uint8_t len = 0;

    if ((len = i2c_smbus_read_byte_data(fd, reg))) {
        perror("failed to read byte");
        exit(1);
    }
    return res;
}

void setI2CMag() {
    if (ioctl(fd, I2C_SLAVE, MAG_ADDR_AM) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

void setI2CAcc() {
    if (ioctl(fd, I2C_SLAVE, ACC_ADDR_AM) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

void setI2CGyr() {
    if (ioctl(fd, I2C_SLAVE, GYR_ADDR_G) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

void initMag(int sensitivity) {
    setI2CMag();
    writeByte(CTRL_REG5_AM, 0xf0);
    writeByte(CTRL_REG6_AM, sensitivity);
    writeByte(CTRL_REG7_AM, 0x00);
}

void initAcc(int sensitivity) {
    setI2CAcc();
    writeByte(CTRL_REG1_AM, 0xa7);
    writeByte(CTRL_REG2_AM, sensitivity);
}

void initGyr(int sensitivity) {
    setI2CGyr();
    writeByte(CTRL_REG1_G, 0x0f);
    writeByte(CTRL_REG4_G, sensitivity);
}

void readMag(float res[3], float conversion) {
    setI2CMag();
	uint8_t xLo = readByte(OUT_X_L_M);
	uint8_t yLo = readByte(OUT_Y_L_M);
	uint8_t zLo = readByte(OUT_Z_L_M);
    int16_t xHi = ((int16_t)readByte(OUT_X_H_M)) << 8;
    int16_t yHi = ((int16_t)readByte(OUT_Y_H_M)) << 8;
    int16_t zHi = ((int16_t)readByte(OUT_Z_H_M)) << 8;
    res[0] = (float)((xHi | xLo) * conversion / 1000);
    res[1] = (float)((yHi | yLo) * conversion / 1000);
    res[2] = (float)((zHi | zLo) * conversion / 1000); 
};

void readAcc(float res[3], float conversion) {
    setI2CAcc();
	uint8_t xLo = readByte(OUT_X_L_A);
	uint8_t yLo = readByte(OUT_Y_L_A);
	uint8_t zLo = readByte(OUT_Z_L_A);
    int16_t xHi = ((int16_t)readByte(OUT_X_H_A)) << 8;
    int16_t yHi = ((int16_t)readByte(OUT_Y_H_A)) << 8;
    int16_t zHi = ((int16_t)readByte(OUT_Z_H_A)) << 8;
    res[0] = (float)((xHi | xLo) * conversion / 1000);
    res[1] = (float)((yHi | yLo) * conversion / 1000);
    res[2] = (float)((zHi | zLo) * conversion / 1000); 
    /* Apply DC offset to set SS values close to 0 */
    res[0] += 1.1;
    res[1] += 1.1;
    res[2] += 1.1;
};

void readGyr(float res[3], float conversion) {
    setI2CGyr();
	uint8_t xLo = readByte(OUT_X_L_G);
	uint8_t yLo = readByte(OUT_Y_L_G);
	uint8_t zLo = readByte(OUT_Z_L_G);
    int16_t xHi = ((int16_t)readByte(OUT_X_H_G)) << 8;
    int16_t yHi = ((int16_t)readByte(OUT_Y_H_G)) << 8;
    int16_t zHi = ((int16_t)readByte(OUT_Z_H_G)) << 8;
    res[0] = (float)((xHi | xLo) * conversion / 1000);
    res[1] = (float)((yHi | yLo) * conversion / 1000);
    res[2] = (float)((zHi | zLo) * conversion / 1000); 
};

void init_imu() {
    if ((fd = open(FILENAME, O_RDWR)) < 0) {
        perror("Failed to open the i2cbus");
        exit(1);
    }
    initAcc(ACCELRANGE_16G);
    initGyr(GYROSCALE_2000DPS);
}

void get_imu_reading(float acc[3], float gyr[3]) {
    readAcc(acc, ACCEL_MG_LSB_16G);
    readGyr(gyr, GYRO_DPS_DIGIT_2000DPS);
}

#ifdef EXECUTABLE
int main(void) {
    #ifdef ZMQ_ENABLE
    printf("ZMQ Enabled!\n");
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    #endif

    init_imu();

    auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        float acc[3] = {0};
        float gyr[3] = {0};
        get_imu_reading(acc, gyr);
        std::chrono::duration<double> time_elapsed = std::chrono::high_resolution_clock::now() - start_time;
        char buffer[80] = {0};
        #ifdef ZMQ_ENABLE
        sprintf(buffer, "%f %f %f %f %f %f %f",
			acc[0], acc[1], acc[2], gyr[0], gyr[1], gyr[2], time_elapsed.count());
        zmq::message_t request;
        socket.recv(&request);
        zmq::message_t measurements(strlen(buffer));
        memcpy(measurements.data(), buffer, strlen(buffer));
        socket.send(measurements);
        #else
        sprintf(buffer, "Acc: %6.2f %6.2f %6.2f | Gyr: %6.2f %6.2f %6.2f | Time: %fs",
			acc[0], acc[1], acc[2], gyr[0], gyr[1], gyr[2], time_elapsed.count());
        printf("%s\n", buffer);
        #endif
        start_time = std::chrono::high_resolution_clock::now();
    }
    return 0;
}
#endif
