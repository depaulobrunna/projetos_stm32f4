#ifndef __MPU60x_H__
#define __MPU60x_H__

#include "stm32f4xx_hal.h"

#define MPU60x_MAX_TEMP				85.0f
#define MPU60x_MIN_TEMP				-40.0f
#define MPU60x_MIN_BYTE_TEMP			0.0f
#define MPU60x_MAX_BYTE_TEMP			65535.0f

#define MPU60x_TEMP_VALUE_RANGE			MPU60x_MAX_TEMP - MPU60x_MIN_TEMP
#define MPU60x_TEMP_BYTE_RANGE			MPU60x_MAX_BYTE_TEMP - MPU60x_MIN_BYTE_TEMP

#define MPU60x_BYTE_TO_FARHENHEIT(BYTE)			((((MPU60x_TEMP_VALUE_RANGE)/ (MPU60x_TEMP_BYTE_RANGE)) * (float)(BYTE)) + MPU60x_MIN_TEMP);
#define MPU60x_FARHENHEIT_TO_CELSIUS(TEMP)  (5.0f / 9.0f) * (TEMP - 32.0f);

typedef enum mpu60x_states_t
{
	MPU60x_WAKE, 				// CYCLE == 0, SLEEP == 0
	MPU60x_WAKE_CYCLE, 	//  CYCLE == 1, SLEEP == 0
	MPU60x_SLEEP 				// CYCLE == 0, SLEEP == 1;
} MPU60x_States;

typedef enum mpu60x_available_t
{
	MPU60x_NOT_AVAILABLE,
	MPU60x_AVAILABLE,
} MPU60x_Available;

typedef enum mpu60x_axis_t
{
	MPU60x_NO_AXIS,
	MPU60x_X_AXIS,
	MPU60x_Y_AXIS,
	MPU60x_Z_AXIS
} MPU60x_Axis;

typedef enum mpu60x_sensor_type_t
{
	MPU60x_GYROSCOPE,
	MPU60x_ACCELEROMETER,
	MPU60x_TEMPERATURE_SENSOR
} MPU60x_Sensor_Type;

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c);

void mpu60x_read_register(uint8_t register_to_read, uint8_t *register_get, uint8_t size);
void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write);
MPU60x_States mpu60x_get_state(void);
void mpu60x_wake(void);
MPU60x_Available mpu60x_available(void);
void mpu60x_set_gyro_cfg(void);
void mpu60x_set_accel_cfg(void);
void mpu60x_set_sample_rate(uint8_t sample_rate_div, uint8_t dlpf_cfg);
void mpu60x_temperature_sensor_enable(void);
void mpu60x_temperature_sensor_disable(void);
uint16_t mpu60x_get_sensor(MPU60x_Sensor_Type sensor, MPU60x_Axis axis);
#endif
