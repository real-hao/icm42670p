/**
 * @file icm42670p.h
 * @brief ICM42670P driver header file
 * @version 1.0.0
 * @date 2023-06-12
 * @author Du Hao
 * @copyright 2023 chiduhasw@gmail.com
*/
#pragma once

#include "esp_err.h"
#include "driver/i2c.h"

/**
 * @brief get real temperature from raw value
 */
#define get_real_temperature(raw)       ((float)(raw) / 128.0f + 25.0f)

/**
 * @brief get real accel from raw value
 */
#define get_real_accel(raw)             ((float)(raw) / 2048.0f)

/**
 * @brief get real gyro from raw value
 */
#define get_real_gyro(raw)              ((float)(raw) / 16.4f)

/**
 * @brief ICM42670P driver error code
 */
typedef struct {
    int16_t accel_x;    /*!< Accelerometer X axis */
    int16_t accel_y;    /*!< Accelerometer Y axis */
    int16_t accel_z;    /*!< Accelerometer Z axis */
    int16_t gyro_x;     /*!< Gyroscope X axis */
    int16_t gyro_y;     /*!< Gyroscope Y axis */
    int16_t gyro_z;     /*!< Gyroscope Z axis */
    int16_t temp;       /*!< Temperature */
}icm42670_raw_t;

/**
 * @brief         Init icm42670p
 * @param[in]     i2c_num: I2C port number
 * @param[in]     address: I2C address
 * @note          If address is 0, use default address 0x68
 * @return        ESP_OK: Init success
 *                ESP_FAIL: Init failed
 */
esp_err_t icm42670p_init(i2c_port_t i2c_num, uint8_t address);

/**
 * @brief       Get raw data from icm42670p
 * @param[out]  raw_data: Raw data
 * @note        This function is usually blocking and must be called after icm42670p_init
 * @return      ESP_OK: Get raw data success
 *              ESP_FAIL: Get raw data failed
 */
esp_err_t icm42670p_get_raw_data(icm42670_raw_t *raw_data);

/**
 * @brief       Deinit icm42670p
 * @return      ESP_OK: Deinit success
 *              ESP_FAIL: Deinit failed
 */
esp_err_t icm42670p_deinit(void);
