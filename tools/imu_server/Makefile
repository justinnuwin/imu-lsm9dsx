CC=g++
CFLAGS=-Wall -Werror -g
LIBS=-lzmq
SERIES0=-DSERIES0 -llsm9ds0
SERIES1=-DSERIES1 -llsm9ds1

SERIES=$(SERIES1)

imu_server: imu_server.cpp
		$(CC) -o $@ $(CFLAGS) $^ $(SERIES) $(LIBS)

.PHONY: clean

clean:
		rm -rf imu_server


