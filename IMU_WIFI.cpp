#include "IMU_WIFI.h"
#include "MPU-9250.h"

IMU_WIFI::IMU_WIFI(char *ssid, char *passwd, MPU9250 imu) {
  IMU_WIFI::ssid = ssid;
  IMU_WIFI::passwd = passwd;
  IMU_WIFI::imu = imu;

  IMU_WIFI::reset_imu_packet();
}

uint8_t IMU_WIFI::send_imu_data() {
  return WIFI_SUCCESS;
}

void IMU_WIFI::reset_imu_packet() {
  IMU_WIFI::imu_packet.number_of_updates = 0;
}

uint8_t IMU_WIFI::next_imu() {
  uint8_t result = WIFI_SUCCESS;
  
  imu.read_gyro(imu_packet.gyro_output + imu_packet.number_of_updates);
  imu.read_accel(imu_packet.accel_output + imu_packet.number_of_updates);
  
  imu_packet.number_of_updates++;

  if (imu_packet.number_of_updates >= PACKET_MAX_IMU_UPDATES) {
    result = send_imu_data();

    reset_imu_packet();

  }

  return result;
}