#ifndef IMU_LSM9DSX_H_
#define IMU_LSM9DSX_H_

#ifdef __cplusplus
extern "C" {
#endif

void initMag(int gain);
void initAcc(int range);
void initGyr(int scale);
void readMag(float res[3], float conversion);
void readAcc(float res[3], float conversion);
void readGyr(float res[3], float conversion);
void init_imu();
void get_imu_reading(float acc[3], float gyr[3]);

#ifdef __cplusplus
}
#endif

#endif
