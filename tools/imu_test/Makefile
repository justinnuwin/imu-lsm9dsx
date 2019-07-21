CC=gcc
CFLAGS=-Wall -Werror -g
SERIES0=-DSERIES0 -llsm9ds0
SERIES1=-DSERIES1 -llsm9ds1

SERIES=$(SERIES1)

imu_test: imu_test.c
		$(CC) -o $@ $(CFLAGS) $^ $(SERIES)

.PHONY: clean

clean:
		rm -rf imu_test


