# Platoon IMU Driver

Justin Nguyen

Adapted from bruce-debruhl/scale_platoon project

Adafruit LSM9DSx
 - Requires root to run due to system-level calls
 - Acceleration is in m s^-2
 - Velocity is in m s^-1
 - Magnetometer is in Gauss
 - Gyro is in Degrees s^-1

## Usage 

```
$ make library
$ sudo make install
```

```
$ make standalone
$ ./imu_test        # Ctrl-c to exit
```

```
$ make zmq_enabled
$ ./imu_server
```

## Dependencies

- libi2c-dev (>=3.1 <4)
- libzmq3-dev	# Only needed for Python interface
- User should be added to the i2c group or commands run with sudo

