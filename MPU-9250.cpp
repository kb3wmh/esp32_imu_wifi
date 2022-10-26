#include <Wire.h>
#include <stdint.h>

#include "MPU-9250.h"
#include "MPU-9250_registers.h"

// Initializes sda and scl variables
MPU9250::MPU9250(int sda, int scl) {
  MPU9250::sda = sda;
  MPU9250::scl = scl; 
}

// Creates Wire session and gets the default settings of the Gyro and Accelerometer
void MPU9250::begin() {
  Wire.begin(MPU9250::sda, MPU9250::scl);

  MPU9250::get_accel_config();
  MPU9250::get_gyro_config();
}

// Reads a single byte from the given address
uint8_t MPU9250::read_byte(uint8_t addr) {
  Wire.beginTransmission(IMU_I2C_ADDR);
  Wire.write(addr);
  Wire.endTransmission();
  
  Wire.requestFrom(IMU_I2C_ADDR, 1);
  return Wire.read();
}

// Gets config byte from GYRO_CONFIG register, saves to struct
uint8_t MPU9250::get_gyro_config() {
  *((uint8_t *) &(MPU9250::gyro_config)) = read_byte(GYRO_CONFIG);

  return IMU_SUCCESS;
}

// Gets config byte from ACCEL_CONFIG register, saves to struct
uint8_t MPU9250::get_accel_config() {
  *((uint8_t *) &(MPU9250::accel_config)) = read_byte(ACCEL_CONFIG);

  // ACCEL_FS_SEL is the sensitivity mode of the accelerometer
  switch(MPU9250::accel_config.ACCEL_FS_SEL) {
    case 0:
      MPU9250::accel_sens_scale = AFS_SEL_0;
      break;
    case 1:
      MPU9250::accel_sens_scale = AFS_SEL_1;
      break;
    case 2:
      MPU9250::accel_sens_scale = AFS_SEL_2;
      break;
    case 3:
      MPU9250::accel_sens_scale = AFS_SEL_3;
      break;
    default:
      MPU9250::accel_sens_scale = 0.0;  
      break;
  }

  return IMU_SUCCESS;
}

// Reads and stores gyro output registers
uint8_t MPU9250::read_gyro(gyro_output_t *gyro_result) {
  if(!gyro_result) {
    return IMU_FAILURE;
  }
  
  gyro_result->x_raw = read_byte(GYRO_XOUT_H) << 8;
  gyro_result->x_raw |= read_byte(GYRO_XOUT_L);

  gyro_result->y_raw = read_byte(GYRO_YOUT_H) << 8;
  gyro_result->y_raw |= read_byte(GYRO_YOUT_L);

  gyro_result->z_raw = read_byte(GYRO_ZOUT_H) << 8;
  gyro_result->z_raw |= read_byte(GYRO_ZOUT_L);

  return IMU_SUCCESS;
}

// Reads and stores accel output registers
uint8_t MPU9250::read_accel(accel_output_t *accel_result) {
  int x_raw, y_raw, z_raw;

  if(!accel_result) {
    return IMU_FAILURE;
  }

  x_raw = read_byte(ACCEL_XOUT_H) << 8;
  x_raw |= read_byte(ACCEL_XOUT_L);

  y_raw = read_byte(ACCEL_YOUT_H) << 8;
  y_raw |= read_byte(ACCEL_YOUT_L);

  z_raw = read_byte(ACCEL_ZOUT_H) << 8;
  z_raw = read_byte(ACCEL_ZOUT_L);

  // Scales accel values to be in 'g' units
  accel_result->x_g = x_raw / MPU9250::accel_sens_scale;
  accel_result->y_g = y_raw / MPU9250::accel_sens_scale;
  accel_result->z_g = z_raw / MPU9250::accel_sens_scale;

  return IMU_SUCCESS;
}