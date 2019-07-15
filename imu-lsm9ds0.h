#ifndef IMU_LSM9DS0_H_
#define IMU_LSM9DS0_H_

#include "imu-lsm9dsx.h"

#define ID_AM   0x49
#define ID_A    0x49
#define ID_M    0x49
#define ID_G    0xd4

#define FILENAME "/dev/i2c-1"
#define MAG_ADDR 0x1D
#define ACC_ADDR 0x1D
#define GYR_ADDR 0x6B

// Shared Accelerometer/Magnetometer Addresses
#define OUT_TEMP_L_AM   0x05
#define OUT_TEMP_H_AM   0x06
#define REG_STATUS_REG_AM 0x07
#define WHO_AM_I_AM	    0x0F
#define INT_CTRL_REG_AM 0x12
#define INT_SRC_REG_AM  0x13
#define CTRL_REG1_AM    0x20
#define CTRL_REG2_AM    0x21
#define CTRL_REG5_AM    0x24
#define CTRL_REG6_AM    0x25
#define CTRL_REG7_AM    0x26

// Magnetometer addresses
#define REG_STATUS_REG_M 0x07
#define OUT_X_L_M   0x08
#define OUT_X_H_M   0x09
#define OUT_Y_L_M   0x0A
#define OUT_Y_H_M   0x0B
#define OUT_Z_L_M   0x0C
#define OUT_Z_H_M   0x0D
#define WHO_AM_I_M  0x0F
#define INT_CTRL_REG_M 0x12
#define INT_SRC_REG_M  0x13
#define CTRL_REG5_M 0x24
#define CTRL_REG6_M 0x25
#define CTRL_REG7_M 0x26

// Accelerometer addresses
#define CTRL_REG1_A 0x20
#define CTRL_REG2_A 0x21
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D

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
#define GRAVITY (9.80665F)

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


// Source Adafruit LSM9DS0 Library (https://github.com/adafruit/Adafruit_LSM9DS0_Library)

typedef enum {
    LSM9DS0_REGISTER_WHO_AM_I_G          = 0x0F,
    LSM9DS0_REGISTER_CTRL_REG1_G         = 0x20,
    LSM9DS0_REGISTER_CTRL_REG3_G         = 0x22,
    LSM9DS0_REGISTER_CTRL_REG4_G         = 0x23,
    LSM9DS0_REGISTER_OUT_X_L_G           = 0x28,
    LSM9DS0_REGISTER_OUT_X_H_G           = 0x29,
    LSM9DS0_REGISTER_OUT_Y_L_G           = 0x2A,
    LSM9DS0_REGISTER_OUT_Y_H_G           = 0x2B,
    LSM9DS0_REGISTER_OUT_Z_L_G           = 0x2C,
    LSM9DS0_REGISTER_OUT_Z_H_G           = 0x2D,
} lsm9ds0GyroRegisters_t;

typedef enum {
    LSM9DS0_REGISTER_TEMP_OUT_L_XM       = 0x05,
    LSM9DS0_REGISTER_TEMP_OUT_H_XM       = 0x06,
    LSM9DS0_REGISTER_STATUS_REG_M        = 0x07,
    LSM9DS0_REGISTER_OUT_X_L_M           = 0x08,
    LSM9DS0_REGISTER_OUT_X_H_M           = 0x09,
    LSM9DS0_REGISTER_OUT_Y_L_M           = 0x0A,
    LSM9DS0_REGISTER_OUT_Y_H_M           = 0x0B,
    LSM9DS0_REGISTER_OUT_Z_L_M           = 0x0C,
    LSM9DS0_REGISTER_OUT_Z_H_M           = 0x0D,
    LSM9DS0_REGISTER_WHO_AM_I_XM         = 0x0F,
    LSM9DS0_REGISTER_INT_CTRL_REG_M      = 0x12,
    LSM9DS0_REGISTER_INT_SRC_REG_M       = 0x13,
    LSM9DS0_REGISTER_CTRL_REG1_XM        = 0x20,
    LSM9DS0_REGISTER_CTRL_REG2_XM        = 0x21,
    LSM9DS0_REGISTER_CTRL_REG5_XM        = 0x24,
    LSM9DS0_REGISTER_CTRL_REG6_XM        = 0x25,
    LSM9DS0_REGISTER_CTRL_REG7_XM        = 0x26,
    LSM9DS0_REGISTER_OUT_X_L_A           = 0x28,
    LSM9DS0_REGISTER_OUT_X_H_A           = 0x29,
    LSM9DS0_REGISTER_OUT_Y_L_A           = 0x2A,
    LSM9DS0_REGISTER_OUT_Y_H_A           = 0x2B,
    LSM9DS0_REGISTER_OUT_Z_L_A           = 0x2C,
    LSM9DS0_REGISTER_OUT_Z_H_A           = 0x2D,
} lsm9ds0MagAccelRegisters_t;

typedef enum {
    LSM9DS0_ACCELRANGE_2G                = (0b000 << 3),
    LSM9DS0_ACCELRANGE_4G                = (0b001 << 3),
    LSM9DS0_ACCELRANGE_6G                = (0b010 << 3),
    LSM9DS0_ACCELRANGE_8G                = (0b011 << 3),
    LSM9DS0_ACCELRANGE_16G               = (0b100 << 3)
} lsm9ds0AccelRange_t;

typedef enum {
    LSM9DS0_ACCELDATARATE_POWERDOWN      = (0b0000 << 4),
    LSM9DS0_ACCELDATARATE_3_125HZ        = (0b0001 << 4),
    LSM9DS0_ACCELDATARATE_6_25HZ         = (0b0010 << 4),
    LSM9DS0_ACCELDATARATE_12_5HZ         = (0b0011 << 4),
    LSM9DS0_ACCELDATARATE_25HZ           = (0b0100 << 4),
    LSM9DS0_ACCELDATARATE_50HZ           = (0b0101 << 4),
    LSM9DS0_ACCELDATARATE_100HZ          = (0b0110 << 4),
    LSM9DS0_ACCELDATARATE_200HZ          = (0b0111 << 4),
    LSM9DS0_ACCELDATARATE_400HZ          = (0b1000 << 4),
    LSM9DS0_ACCELDATARATE_800HZ          = (0b1001 << 4),
    LSM9DS0_ACCELDATARATE_1600HZ         = (0b1010 << 4)
} lm9ds0AccelDataRate_t;

typedef enum {
    LSM9DS0_MAGGAIN_2GAUSS               = (0b00 << 5),  // +/- 2 gauss
    LSM9DS0_MAGGAIN_4GAUSS               = (0b01 << 5),  // +/- 4 gauss
    LSM9DS0_MAGGAIN_8GAUSS               = (0b10 << 5),  // +/- 8 gauss
    LSM9DS0_MAGGAIN_12GAUSS              = (0b11 << 5)   // +/- 12 gauss
} lsm9ds0MagGain_t;

typedef enum {
    LSM9DS0_MAGDATARATE_3_125HZ          = (0b000 << 2),
    LSM9DS0_MAGDATARATE_6_25HZ           = (0b001 << 2),
    LSM9DS0_MAGDATARATE_12_5HZ           = (0b010 << 2),
    LSM9DS0_MAGDATARATE_25HZ             = (0b011 << 2),
    LSM9DS0_MAGDATARATE_50HZ             = (0b100 << 2),
    LSM9DS0_MAGDATARATE_100HZ            = (0b101 << 2)
} lsm9ds0MagDataRate_t;

typedef enum {
    LSM9DS0_GYROSCALE_245DPS             = (0b00 << 4),  // +/- 245 degrees per second rotation
    LSM9DS0_GYROSCALE_500DPS             = (0b01 << 4),  // +/- 500 degrees per second rotation
    LSM9DS0_GYROSCALE_2000DPS            = (0b10 << 4)   // +/- 2000 degrees per second rotation
} lsm9ds0GyroScale_t;
#endif
