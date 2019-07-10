#ifndef IMU_LSM9DS0_H
#define IMU_LSM9DS0_H

#define ID_AM 0x49
#define ID_G  0xd4

#define FILENAME "/dev/i2c-1"
#define MAG_ADDR_AM 0x1D
#define ACC_ADDR_AM 0x1D
#define GYR_ADDR_G  0x6B

// Shared accelerometer/magnetometer addresses
#define WHO_AM_I_AM	0x0f
#define INT_CTRL_REG_M  0x12
#define INT_SRC_REG_M   0x13
#define CTRL_REG1_AM    0x20
#define CTRL_REG2_AM    0x21
#define CTRL_REG5_AM    0x24
#define CTRL_REG6_AM    0x25
#define CTRL_REG7_AM    0x26

// Magnetometer addresses
#define STATUS_REG_M 0x07
#define OUT_X_L_M    0x08
#define OUT_X_H_M    0x09
#define OUT_Y_L_M    0x0A
#define OUT_Y_H_M    0x0B
#define OUT_Z_L_M    0x0C
#define OUT_Z_H_M    0x0D

// Accelerometer addresses
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D

// Magnetometer/Accelerometer temperature sensor addresses
#define OUT_TEMP_L_AM 0x05
#define OUT_TEMP_H_AM 0x06

// Gyroscope addresses
#define WHO_AM_I_G  0x0F
#define CTRL_REG1_G 0x20
#define CTRL_REG3_G 0x22
#define CTRL_REG4_G 0x23
#define OUT_X_L_G   0x28
#define OUT_X_H_G   0x29
#define OUT_Y_L_G   0x2A
#define OUT_Y_H_G   0x2B
#define OUT_Z_L_G   0x2C
#define OUT_Z_H_G   0x2D


// Settings
#define ACCELRANGE_2G           0x0 << 3
#define ACCELRANGE_4G           0x1 << 3
#define ACCELRANGE_6G           0x2 << 3
#define ACCELRANGE_8G           0x3 << 3
#define ACCELRANGE_16G          0x8 << 3

#define ACCELDATARATE_POWERDOWN 0x0 << 4
#define ACCELDATARATE_3_125HZ   0x1 << 4
#define ACCELDATARATE_6_25HZ    0x2 << 4
#define ACCELDATARATE_12_5HZ    0x3 << 4
#define ACCELDATARATE_25HZ      0x4 << 4
#define ACCELDATARATE_50HZ      0x5 << 4
#define ACCELDATARATE_100HZ     0x6 << 4
#define ACCELDATARATE_200HZ     0x7 << 4
#define ACCELDATARATE_400HZ     0x8 << 4
#define ACCELDATARATE_800HZ     0x9 << 4
#define ACCELDATARATE_1600HZ    0xa << 4

#define MAGGAIN_2GAUSS          0x0 << 5
#define MAGGAIN_4GAUSS          0x1 << 5
#define MAGGAIN_8GAUSS          0x2 << 5
#define MAGGAIN_12GAUSS         0x3 << 5

#define MAGDATARATE_3_125HZ     0x0 << 2
#define MAGDATARATE_6_25HZ      0x1 << 2
#define MAGDATARATE_12_5HZ      0x2 << 2
#define MAGDATARATE_25HZ        0x3 << 2
#define MAGDATARATE_50HZ        0x4 << 2
#define MAGDATARATE_100HZ       0x5 << 2

#define GYROSCALE_245DPS        0x0 << 4
#define GYROSCALE_500DPS        0x1 << 4
#define GYROSCALE_2000DPS       0x2 << 4

/* Conversions */
#define ACCEL_MG_LSB_2G  (0.061F)
#define ACCEL_MG_LSB_4G  (0.122F)
#define ACCEL_MG_LSB_6G  (0.183F)
#define ACCEL_MG_LSB_8G  (0.244F)
#define ACCEL_MG_LSB_16G (0.732F) // Is this right? Was expecting 0.488F

#define MAG_MGAUSS_2GAUSS      (0.08F)
#define MAG_MGAUSS_4GAUSS      (0.16F)
#define MAG_MGAUSS_8GAUSS      (0.32F)
#define MAG_MGAUSS_12GAUSS     (0.48F)

#define GYRO_DPS_DIGIT_245DPS      (0.00875F)
#define GYRO_DPS_DIGIT_500DPS      (0.01750F)
#define GYRO_DPS_DIGIT_2000DPS     (0.07000F)

#define TEMP_LSB_DEGREE_CELSIUS    (8)  // 1°C = 8, 25° = 200, etc.

void initMag(int sensitivity);
void initAcc(int sensitivity);
void initGyr(int sensitivity);
void readMag(float res[3], float conversion);
void readAcc(float res[3], float conversion);
void readGyr(float res[3], float conversion);
void init_imu();
void get_imu_reading(float acc[3], float gyr[3]);
#endif
