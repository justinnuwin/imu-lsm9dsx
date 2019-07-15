#ifndef IMU_LSM9DS0_H_
#define IMU_LSM9DS0_H_

#include "imu-lsm9dsx.h"

#define ID_AG   0x6F
#define ID_A    0x6F
#define ID_G    0x6F
#define ID_M    0x3D

#define FILENAME "/dev/i2c-1"
#define MAG_ADDR 0x1E
#define ACC_ADDR 0x6B
#define GYR_ADDR 0x6B

// Shared Accelerometer/Gyroscope Addresses
#define WHO_AM_I_AG	    0x0F
#define CTRL_REG1_AG    0x10
#define CTRL_REG2_AG    0x11
#define CTRL_REG3_AG    0x12
#define OUT_TEMP_L_AG   0x15
#define OUT_TEMP_H_AG   0x16
#define REG_STATUS_REG_AG 0x17
#define CTRL_REG4_AG    0x1E
#define CTRL_REG5_AG    0x1F
#define CTRL_REG6_AG    0x20
#define CTRL_REG7_AG    0x21
#define CTRL_REG8_AG    0x22
#define CTRL_REG9_AG    0x23
#define CTRL_REG10_AG   0x24

// Gyroscope addresses
#define WHO_AM_I_G  0x0F
#define CTRL_REG1_G 0x10
#define CTRL_REG2_G 0x11
#define CTRL_REG3_G 0x12
#define OUT_X_L_G   0x18
#define OUT_X_H_G   0x19
#define OUT_Y_L_G   0x1A
#define OUT_Y_H_G   0x1B
#define OUT_Z_L_G   0x1C
#define OUT_Z_H_G   0x1D

// Accelerometer addresses
#define WHO_AM_I_A	    0x0F
#define CTRL_REG5_A     0x1F
#define CTRL_REG6_A     0x20
#define CTRL_REG7_A     0x21
#define OUT_X_L_A       0x28
#define OUT_X_H_A       0x29
#define OUT_Y_L_A       0x2A
#define OUT_Y_H_A       0x2B
#define OUT_Z_L_A       0x2C
#define OUT_Z_H_A       0x2D

// Magnetometer addresses
#define WHO_AM_I_M  0x0F
#define CTRL_REG1_M 0x20
#define CTRL_REG2_M 0x21
#define CTRL_REG3_M 0x22
#define CTRL_REG4_M 0x23
#define CTRL_REG5_M 0x24
#define REG_STATUS_REG_M 0x27
#define OUT_X_L_M   0x28
#define OUT_X_H_M   0x29
#define OUT_Y_L_M   0x2A
#define OUT_Y_H_M   0x2B
#define OUT_Z_L_M   0x2C
#define OUT_Z_H_M   0x2D
#define REG_CFG_M   0x30
#define INT_SRC_M   0x31

// Settings
#define ACCELRANGE_2G           0x0 << 3
#define ACCELRANGE_16G          0x1 << 3
#define ACCELRANGE_4G           0x2 << 3
#define ACCELRANGE_8G           0x3 << 3

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

#define MAGGAIN_4GAUSS          0x0 << 5
#define MAGGAIN_8GAUSS          0x1 << 5
#define MAGGAIN_12GAUSS         0x2 << 5
#define MAGGAIN_16GAUSS         0x3 << 5

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
#define ACCEL_MG_LSB_8G  (0.244F)
#define ACCEL_MG_LSB_16G (0.732F) // Is this right? Was expecting 0.488F

#define MAG_MGAUSS_4GAUSS      (0.16F)
#define MAG_MGAUSS_8GAUSS      (0.32F)
#define MAG_MGAUSS_12GAUSS     (0.48F)
#define MAG_MGAUSS_16GAUSS     (0.58F)

#define GYRO_DPS_DIGIT_245DPS      (0.00875F)
#define GYRO_DPS_DIGIT_500DPS      (0.01750F)
#define GYRO_DPS_DIGIT_2000DPS     (0.07000F)

#define TEMP_LSB_DEGREE_CELSIUS    (8)  // 1°C = 8, 25° = 200, etc.

// Source Adafruit LSM9DS1 Library (https://github.com/adafruit/Adafruit_LSM9DS1_Library)

typedef enum {
    LSM9DS1_REGISTER_WHO_AM_I_XG         = 0x0F,
    LSM9DS1_REGISTER_CTRL_REG1_G         = 0x10,
    LSM9DS1_REGISTER_CTRL_REG2_G         = 0x11,
    LSM9DS1_REGISTER_CTRL_REG3_G         = 0x12,
    LSM9DS1_REGISTER_TEMP_OUT_L          = 0x15,
    LSM9DS1_REGISTER_TEMP_OUT_H          = 0x16,
    LSM9DS1_REGISTER_STATUS_REG          = 0x17,
    LSM9DS1_REGISTER_OUT_X_L_G           = 0x18,
    LSM9DS1_REGISTER_OUT_X_H_G           = 0x19,
    LSM9DS1_REGISTER_OUT_Y_L_G           = 0x1A,
    LSM9DS1_REGISTER_OUT_Y_H_G           = 0x1B,
    LSM9DS1_REGISTER_OUT_Z_L_G           = 0x1C,
    LSM9DS1_REGISTER_OUT_Z_H_G           = 0x1D,
    LSM9DS1_REGISTER_CTRL_REG4           = 0x1E,
    LSM9DS1_REGISTER_CTRL_REG5_XL        = 0x1F,
    LSM9DS1_REGISTER_CTRL_REG6_XL        = 0x20,
    LSM9DS1_REGISTER_CTRL_REG7_XL        = 0x21,
    LSM9DS1_REGISTER_CTRL_REG8           = 0x22,
    LSM9DS1_REGISTER_CTRL_REG9           = 0x23,
    LSM9DS1_REGISTER_CTRL_REG10          = 0x24,

    LSM9DS1_REGISTER_OUT_X_L_XL          = 0x28,
    LSM9DS1_REGISTER_OUT_X_H_XL          = 0x29,
    LSM9DS1_REGISTER_OUT_Y_L_XL          = 0x2A,
    LSM9DS1_REGISTER_OUT_Y_H_XL          = 0x2B,
    LSM9DS1_REGISTER_OUT_Z_L_XL          = 0x2C,
    LSM9DS1_REGISTER_OUT_Z_H_XL          = 0x2D,
} lsm9ds1AccGyroRegisters_t;

typedef enum {
    LSM9DS1_REGISTER_WHO_AM_I_M         = 0x0F,
    LSM9DS1_REGISTER_CTRL_REG1_M        = 0x20,
    LSM9DS1_REGISTER_CTRL_REG2_M        = 0x21,
    LSM9DS1_REGISTER_CTRL_REG3_M        = 0x22,
    LSM9DS1_REGISTER_CTRL_REG4_M        = 0x23,
    LSM9DS1_REGISTER_CTRL_REG5_M        = 0x24,
    LSM9DS1_REGISTER_STATUS_REG_M       = 0x27,
    LSM9DS1_REGISTER_OUT_X_L_M          = 0x28,
    LSM9DS1_REGISTER_OUT_X_H_M          = 0x29,
    LSM9DS1_REGISTER_OUT_Y_L_M          = 0x2A,
    LSM9DS1_REGISTER_OUT_Y_H_M          = 0x2B,
    LSM9DS1_REGISTER_OUT_Z_L_M          = 0x2C,
    LSM9DS1_REGISTER_OUT_Z_H_M          = 0x2D,
    LSM9DS1_REGISTER_CFG_M              = 0x30,
    LSM9DS1_REGISTER_INT_SRC_M          = 0x31,
} lsm9ds1MagRegisters_t;

typedef enum {
    LSM9DS1_ACCELRANGE_2G                = (0b00 << 3),
    LSM9DS1_ACCELRANGE_16G               = (0b01 << 3),
    LSM9DS1_ACCELRANGE_4G                = (0b10 << 3),
    LSM9DS1_ACCELRANGE_8G                = (0b11 << 3),
} lsm9ds1AccelRange_t;

typedef enum {
    LSM9DS1_ACCELDATARATE_POWERDOWN      = (0b0000 << 4),
    LSM9DS1_ACCELDATARATE_3_125HZ        = (0b0001 << 4),
    LSM9DS1_ACCELDATARATE_6_25HZ         = (0b0010 << 4),
    LSM9DS1_ACCELDATARATE_12_5HZ         = (0b0011 << 4),
    LSM9DS1_ACCELDATARATE_25HZ           = (0b0100 << 4),
    LSM9DS1_ACCELDATARATE_50HZ           = (0b0101 << 4),
    LSM9DS1_ACCELDATARATE_100HZ          = (0b0110 << 4),
    LSM9DS1_ACCELDATARATE_200HZ          = (0b0111 << 4),
    LSM9DS1_ACCELDATARATE_400HZ          = (0b1000 << 4),
    LSM9DS1_ACCELDATARATE_800HZ          = (0b1001 << 4),
    LSM9DS1_ACCELDATARATE_1600HZ         = (0b1010 << 4)
} lm9ds1AccelDataRate_t;

typedef enum {
    LSM9DS1_MAGGAIN_4GAUSS               = (0b00 << 5),  // +/- 4 gauss
    LSM9DS1_MAGGAIN_8GAUSS               = (0b01 << 5),  // +/- 8 gauss
    LSM9DS1_MAGGAIN_12GAUSS              = (0b10 << 5),  // +/- 12 gauss
    LSM9DS1_MAGGAIN_16GAUSS              = (0b11 << 5)   // +/- 16 gauss
} lsm9ds1MagGain_t;

typedef enum {
    LSM9DS1_MAGDATARATE_3_125HZ          = (0b000 << 2),
    LSM9DS1_MAGDATARATE_6_25HZ           = (0b001 << 2),
    LSM9DS1_MAGDATARATE_12_5HZ           = (0b010 << 2),
    LSM9DS1_MAGDATARATE_25HZ             = (0b011 << 2),
    LSM9DS1_MAGDATARATE_50HZ             = (0b100 << 2),
    LSM9DS1_MAGDATARATE_100HZ            = (0b101 << 2)
} lsm9ds1MagDataRate_t;

typedef enum {
    LSM9DS1_GYROSCALE_245DPS             = (0b00 << 3),  // +/- 245 degrees per second rotation
    LSM9DS1_GYROSCALE_500DPS             = (0b01 << 3),  // +/- 500 degrees per second rotation
    LSM9DS1_GYROSCALE_2000DPS            = (0b11 << 3)   // +/- 2000 degrees per second rotation
} lsm9ds1GyroScale_t;
#endif
