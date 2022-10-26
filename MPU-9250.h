#ifndef MPU_9250_H
#define MPU_9250_H

#include <stdint.h>

#define IMU_FAILURE 0
#define IMU_SUCCESS 1

typedef struct {
  uint8_t XGYRO_Ct_en : 1;
  uint8_t YGYRO_Ct_en : 1;
  uint8_t ZGYRO_Ct_en : 1;
  uint8_t GYRO_FS_SEL : 2;
  uint8_t UNUSED_PAD  : 1;
  uint8_t FCHOICE_B   : 2;
} gyro_config_t;

typedef struct {
  uint8_t ax_st_en     : 1;
  uint8_t ay_st_en     : 1;
  uint8_t az_st_en     : 1;
  uint8_t ACCEL_FS_SEL : 2;
  uint8_t UNUSED_PAD   : 3;
} accel_config_t;

typedef struct {
  int16_t x_raw;
  int16_t y_raw;
  int16_t z_raw;
} gyro_output_t;

typedef struct {
  float x_g;
  float y_g;
  float z_g;
} accel_output_t;

class MPU9250 {
private:
  int sda, scl;
  float accel_sens_scale;
  gyro_config_t gyro_config;
  accel_config_t accel_config;

  uint8_t read_byte(uint8_t addr);
  uint8_t get_gyro_config();
  uint8_t get_accel_config();

public:
  MPU9250(int sda, int scl);
  void begin();
  uint8_t read_gyro(gyro_output_t *gyro_result);
  uint8_t read_accel(accel_output_t *accel_result);
};

#endif