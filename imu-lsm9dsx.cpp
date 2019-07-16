#ifdef SERIES0
#include "imu-lsm9ds0.h"
#elif SERIES1
#include "imu-lsm9ds1.h"
#endif

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

#include "i2c.h"

#ifdef ZMQ_ENABLE
#include <zmq.hpp>
#include <string.h>
#endif

using namespace std;

int fd;

void setI2CMag() {
    if (ioctl(fd, I2C_SLAVE, MAG_ADDR) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

void setI2CAcc() {
    if (ioctl(fd, I2C_SLAVE, ACC_ADDR) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

void setI2CGyr() {
    if (ioctl(fd, I2C_SLAVE, GYR_ADDR) < 0) {
        perror("Could not set slave address");
        exit(1);
    }
}

// TODO: Check Series0 inits

void initAcc(int range) {
    setI2CAcc();
#ifdef SERIES0
    writeByte(CTRL_REG1_A, 0xA7);
    writeByte(CTRL_REG2_A, range);
#elif SERIES1
    writeByte(CTRL_REG5_A, 0x38);   // Enable X, Y, Z
    writeByte(CTRL_REG6_A, 0xC0);   // 1 KHz out data rate, BW set by ODR, 408Hz anti-aliasing
    uint8_t reg = readByte(CTRL_REG6_A);
    reg &= ~(0b00011000);
    reg |= range;
    writeByte(CTRL_REG6_A, reg);
#endif
}

void initGyr(int scale) {
    setI2CGyr();
#ifdef SERIES0
    writeByte(CTRL_REG1_G, 0x0F);
    writeByte(CTRL_REG4_G, scale);
#elif SERIES1
    writeByte(CTRL_REG1_G, 0xC0);   // Enable X, Y, Z
    uint8_t reg = readByte(CTRL_REG1_G);
    reg &= ~(0b00011000);
    reg |= scale;
    writeByte(CTRL_REG1_G, reg);
#endif
}

void initMag(int gain) {
    setI2CMag();
#ifdef SERIES0
    writeByte(CTRL_REG5_M, 0xF0);
    writeByte(CTRL_REG6_M, gain);
    writeByte(CTRL_REG7_M, 0x00);
#elif SERIES1
    writeByte(CTRL_REG3_M, 0x00);   // Continuous mode
    uint8_t reg = readByte(CTRL_REG2_M);
    reg &= ~(0b01100000);
    reg |= gain;
    writeByte(CTRL_REG2_M, reg);

#endif
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
    res[0] = (float)((xHi | xLo) * conversion / 1000) * GRAVITY;
    res[1] = (float)((yHi | yLo) * conversion / 1000) * GRAVITY;
    res[2] = (float)((zHi | zLo) * conversion / 1000) * GRAVITY; 
};

void readGyr(float res[3], float conversion) {
    setI2CGyr();
	uint8_t xLo = readByte(OUT_X_L_G);
	uint8_t yLo = readByte(OUT_Y_L_G);
	uint8_t zLo = readByte(OUT_Z_L_G);
    int16_t xHi = ((int16_t)readByte(OUT_X_H_G)) << 8;
    int16_t yHi = ((int16_t)readByte(OUT_Y_H_G)) << 8;
    int16_t zHi = ((int16_t)readByte(OUT_Z_H_G)) << 8;
    res[0] = (float)((xHi | xLo) * conversion);
    res[1] = (float)((yHi | yLo) * conversion);
    res[2] = (float)((zHi | zLo) * conversion); 
};

// TODO: Implement reading temperature sensor

void init_imu() {
    if ((fd = open(FILENAME, O_RDWR)) < 0) {
        perror("Failed to open the i2cbus");
        exit(1);
    }
    // TODO: Softreset each sensor
    // TODO: Check WHO_AM_I
    initAcc(ACCELRANGE_8G);
    initGyr(GYROSCALE_500DPS);
}

void get_imu_reading(float acc[3], float gyr[3]) {
    readAcc(acc, ACCEL_MG_LSB_8G);
    readGyr(gyr, GYRO_DPS_DIGIT_500DPS);
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
