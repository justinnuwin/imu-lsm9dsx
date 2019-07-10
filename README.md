# Platoon IMU Driver

Justin Nguyen

Adapted from bruce-debruhl/scale_platoon project

Adafruit LSM9DS0
 - Requires root to run due to system-level calls
 - Acceleration is in m s^-2
 - Velocity is in m s^-1
 - Magnetometer is in Gauss
 - Gyro is in Degrees s^-1

## Usage 

`$ sudo ./imu`

Ctrl-c to exit

## Dependencies

- libi2c-dev
- libzmq3-dev	# Python interface

## Build instructions

`$ make`

