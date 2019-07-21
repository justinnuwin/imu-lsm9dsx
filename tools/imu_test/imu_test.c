#ifdef SERIES0
#include <lsm9ds0.h>
#elif SERIES1
#include <lsm9ds1.h>
#endif

#include <stdio.h>

int main(void) {
    init_imu();

    while (1) {
        float acc[3] = {0};
        float gyr[3] = {0};
        get_imu_reading(acc, gyr);
        printf("Accelerometer (X Y Z): %7.2f %7.2f %7.2f | Gyroscope (X Y Z): %7.2f %7.2f %7.2f\n",
                acc[0], acc[1], acc[2], gyr[0], gyr[1], gyr[2]);
    }
    return 0;
}
