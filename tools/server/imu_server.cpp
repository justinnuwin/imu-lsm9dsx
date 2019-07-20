#ifdef SERIES0
#include <lsm9ds0.h>
#elif SERIES1
#include <lsm9ds1.h>
#endif

#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zmq.hpp>

int main(void) {
    // TODO: Add option to specify port
    // TODO: Add option to run as a daemon rather than requiring user to use & or nohup
    // TODO: Add verbose/logging mode
    printf("ZMQ Enabled!\n");
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    init_imu();

    auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        float acc[3] = {0};
        float gyr[3] = {0};
        get_imu_reading(acc, gyr);
        std::chrono::duration<double> time_elapsed = std::chrono::high_resolution_clock::now() - start_time;
        char buffer[80] = {0};
        sprintf(buffer, "%f %f %f %f %f %f %f",
			acc[0], acc[1], acc[2], gyr[0], gyr[1], gyr[2], time_elapsed.count());
        zmq::message_t request;
        socket.recv(&request);
        zmq::message_t measurements(strlen(buffer));
        memcpy(measurements.data(), buffer, strlen(buffer));
        socket.send(measurements);
        start_time = std::chrono::high_resolution_clock::now();
    }
    return 0;
}
