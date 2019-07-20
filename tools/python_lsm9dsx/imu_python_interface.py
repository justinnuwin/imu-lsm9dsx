import numpy as np
import subprocess
import sys
import zmq

BIAS_SAMP_COUNT = 200
G = 9.801

class ImuInterface:
    def __init__(self):
        # TODO: Check if server already running and connect otherwise start it first
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.REQ)
        try:
            self.socket.connect("tcp://localhost:5555")
        except:
            print("Failed to connect to IMU server via zmq socket", file=sys.stderr)
            sys.exit(1)

        self.acc = np.ndarray((3, 1))
        self.gyr = np.ndarray((3, 1))
        self.dt = 0

        self.acc_bias = np.zeros((3, 1))
        self.gyr_bias = np.zeros((3, 1))
        self.g_bias = np.zeros((3, 1))

        self.get_bias()

    def request_measurement(self):
        self.socket.send(b"0")

    def receive_measurement(self):
        message = self.socket.recv()
        values = message.split(" ")
        values = [float(v) for v in values]
        self.acc = np.array(values[0:3]).reshape((3, 1))
        self.gyr = np.array(values[3:6]).reshape((3, 1))
        self.dt = values[-1]

    def get_measurement(self):
        self.request_measurement()
        self.receive_measurement()
        # acc = np.subtract(self.acc, self.acc_bias)
        acc = np.subtract(self.acc, self.g_bias)
        gyr = np.subtract(self.gyr, self.gyr_bias)
        return acc, gyr, self.dt

    def get_gravity(self):
        self.request_measurement()
        self.receive_measurement()
        acc = np.subtract(self.acc, self.g_bias)
        return acc
    
    def get_bias(self):
        """ Assume IMU is not moving """
        acc_samples = np.zeros((3, 1))
        gyr_samples = np.zeros((3, 1))
        for i in range(BIAS_SAMP_COUNT):
            acc, gyr, dt = self.get_measurement()
            acc_samples = np.add(acc_samples, acc)
            gyr_samples = np.add(gyr_samples, gyr)
        self.acc_bias = np.divide(acc_samples, BIAS_SAMP_COUNT)
        self.gyr_bias = np.divide(gyr_samples, BIAS_SAMP_COUNT)
        self.g_bias = np.copy(self.acc_bias)
        self.g_bias[2] = self.acc_bias[2] - G


if __name__ == "__main__":
    imu = ImuInterface()
    print("Acc Bias", imu.acc_bias)
    print("Gyr Bias", imu.gyr_bias)
    print("G Bias", imu.g_bias)
    for i in range(10):
        print(imu.get_measurement())

