CC=g++
CFLAGS=-Wall -Werror -g

library: imu-lsm9ds0.cpp
	$(CC) -o imu.o $(CFLAGS) -c $<

standalone: imu-lsm9ds0.cpp
	$(CC) -o imu_test $(CFLAGS) $< -DEXECUTABLE

zmq_enabled: imu-lsm9ds0.cpp
	$(CC) -o imu $(CFLAGS) $< -DZMQ_ENABLE -DEXECUTABLE -lzmq

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf imu

