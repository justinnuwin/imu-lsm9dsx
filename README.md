# Platoon IMU Driver

Justin Nguyen

LSM9DS0 or LSM9DS1
 - Requires root to run due to system-level calls or user be in the i2c group
 - Acceleration is in m s^-2
 - Velocity is in m s^-1
 - Magnetometer is in Gauss
 - Gyro is in Degrees s^-1

## Usage 

To install the library and build the tools run the following:

```
$ make
$ sudo make install
```

To install the Python interface run the following:

```
$ make python_interface
$ sudo make install_python_interface
```

## Example

An example program is provided in tools/imu_test. Instructions below:

```
$ cd tools/imu_test
$ make
$ ./imu_test    
```

Press Ctrl+c to close the test utility.

## Removal

```
$ sudo make uninstall
$ make clean
```

If the python interface is installed the following can be run to remove it:

```
$ sudo make uninstall_python_interface
$ make clean
```

## Dependencies

- libi2c-dev (>=3.1 <4)

To use the python interface the following is required:

- python2 or python3
- libzmq3-dev
- setuptools
