#ifdef SERIES0
#include <lsm9ds0.h>
#elif SERIES1
#include <lsm9ds1.h>
#endif

#include <chrono>
#include <cstdio>
#include <cstring>
#include <zmq.hpp>

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

int main(void) {
    // TODO: Add option to specify port
    // TODO: Add option to run as a daemon rather than requiring user to use & or nohup
    // TODO: Add verbose/logging mode
    printf("ZMQ Enabled!\n");
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    init_imu();

    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
    // time_t start_time_timet = chrono::high_resolution_clock::to_time_t(start_time);
    // cout << "Started at " << put_time(localtime(&start_time_timet), "%T") << endl;
    while (true) {
        float acc[3] = {0};
        float gyr[3] = {0};
        get_imu_reading(acc, gyr);
        zmq::message_t request;
        socket.recv(&request);
        chrono::duration<double> time_elapsed = chrono::high_resolution_clock::now() - start_time;
        start_time = chrono::high_resolution_clock::now();
        char buffer[80] = {0};
        sprintf(buffer, "%f %f %f %f %f %f %f",
			acc[0], acc[1], acc[2], gyr[0], gyr[1], gyr[2], time_elapsed.count());
        zmq::message_t measurements(strlen(buffer));
        memcpy(measurements.data(), buffer, strlen(buffer));
        socket.send(measurements);
    }
    return 0;
}
