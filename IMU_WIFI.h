#ifndef IMU_WIFI_H
#define IMU_WIFI_H

#include "MPU-9250.h"

#define PACKET_MAX_IMU_UPDATES 100

#define WIFI_SUCCESS 1
#define WIFI_FAILURE 0

typedef struct __attribute__((__packed__)){
  uint8_t number_of_updates;
  accel_output_t accel_output[PACKET_MAX_IMU_UPDATES];
  gyro_output_t gyro_output[PACKET_MAX_IMU_UPDATES]; 
} imu_packet_t;

class IMU_WIFI {
private:
  MPU9250 imu;
  char *ssid, *passwd;
  imu_packet_t imu_packet;
  uint8_t send_imu_data();
  void reset_imu_packet();

public:
  IMU_WIFI(char *ssid, char *passwd, MPU9250 imu);
  uint8_t next_imu();
};


#endif