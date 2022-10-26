#include "MPU-9250.h" // Wrote my own library so I can reuse this work for the project
#include "IMU_WIFI.h"

const uint8_t sda = 21;
const uint8_t scl = 22;
const uint16_t polling_rate_hz = 50;

MPU9250 imu = MPU9250(sda, scl);
imu_packet_t imu_packet;

unsigned long last_update_time = 0;


void setup() {
  imu.begin();
  Serial.begin(9600);

  imu_packet.number_of_updates = 0;
}

void loop() {
  if (millis() - last_update_time > (1000 / polling_rate_hz)) {
    

    last_update_time = millis();
  }



  // Serial.print("X_accel:"); Serial.print(accel_output.x_g); Serial.print(",");
  // Serial.print("Y_accel:"); Serial.print(accel_output.y_g); Serial.print(",");
  // Serial.print("Z_accel:"); Serial.print(accel_output.z_g); Serial.print(",");

  // Serial.print("X_gyro:"); Serial.print(gyro_output.x_raw); Serial.print(",");
  // Serial.print("Y_gyro:"); Serial.print(gyro_output.y_raw); Serial.print(",");
  // Serial.print("Z_gyro:"); Serial.println(gyro_output.z_raw);
}
