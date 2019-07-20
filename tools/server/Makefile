CC=g++
CFLAGS=-Wall -Werror -g
LIBS=-llsm9dsx -lzmq
SERIES=-D SERIES1

imu_server: imu_server.cpp
	$(CC) -o imu_server $(CFLAGS) $(SERIES) $^ $(LIBS)

.PHONY: clean

clean:
	rm -rf imu_server

