CC=g++
CFLAGS=-Wall -Werror -g
SERIES=-D SERIES1

library: imu-lsm9dsx.o i2c.o

standalone: executable-imu-lsm9dsx.o i2c.o
	$(CC) -o imu_test $(CFLAGS) $^

zmq_enabled: zmq-executable-imu-lsm9dsx.o i2c.o
	$(CC) -o imu_server $(CFLAGS) $^ -lzmq

imu-lsm9dsx.o: imu-lsm9dsx.cpp
	$(CC) -o $@ $(CFLAGS) $(SERIES) -c $<

executable-imu-lsm9dsx.o: imu-lsm9dsx.cpp
	$(CC) -o $@ $(CFLAGS) $(SERIES) -DEXECUTABLE -c $<

zmq-executable-imu-lsm9dsx.o: imu-lsm9dsx.cpp
	$(CC) -o $@ $(CFLAGS) $(SERIES) -DEXECUTABLE -DZMQ_ENABLE -c $<

i2c.o: i2c.c i2c.h
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf imu_test
	rm -rf imu_server
	rm -rf *.pyc
	rm -rf __pycache__

