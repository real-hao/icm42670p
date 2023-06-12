/**
 * @file icm42670p.c
 * @brief ICM42670P driver source file
 * @version 1.0.0
 * @date 2023-06-12
 * @author Du Hao
 * @copyright 2023 chiduhasw@gmail.com
*/

#include "icm42670p.h"
#include "esp_check.h"

static const char *TAG = "icm42670p";
static uint8_t g_address = 0b1101000;
static i2c_port_t g_i2c_num = 0;

esp_err_t icm42670p_init(i2c_port_t i2c_num, uint8_t address){
    if(address > 0){
        g_address = address;
    }
    g_i2c_num = i2c_num;
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    if(handle == NULL){
        return ESP_FAIL;
    }
    ESP_RETURN_ON_ERROR(i2c_master_start(handle), TAG, "i2c_master_start");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, g_address << 1 | I2C_MASTER_WRITE, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, 0x1F, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, 0x0F, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_stop(handle), TAG, "i2c_master_stop");
    ESP_RETURN_ON_ERROR(i2c_master_cmd_begin(i2c_num, handle, portMAX_DELAY), TAG, "i2c_master_cmd_begin");
    i2c_cmd_link_delete(handle);
    return ESP_OK;
}

esp_err_t icm42670p_get_raw_data(icm42670_raw_t *raw_data){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(cmd == NULL){
        return ESP_FAIL;
    }
    ESP_RETURN_ON_ERROR(i2c_master_start(cmd), TAG, "i2c_master_start");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(cmd, g_address << 1 | I2C_MASTER_WRITE, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(cmd, 0x09, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_start(cmd), TAG, "i2c_master_start");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(cmd, g_address << 1 | I2C_MASTER_READ, true), TAG, "i2c_master_write_byte");
    uint8_t data[14] = { 0 };
    for(uint8_t i = 0; i < 14; i++){
        ESP_RETURN_ON_ERROR(i2c_master_read_byte(cmd, &data[i], I2C_MASTER_ACK), TAG, "i2c_master_read_byte");
    }
    ESP_RETURN_ON_ERROR(i2c_master_read_byte(cmd, &data[14], I2C_MASTER_NACK), TAG, "i2c_master_read_byte");
    ESP_RETURN_ON_ERROR(i2c_master_stop(cmd), TAG, "i2c_master_stop");
    ESP_RETURN_ON_ERROR(i2c_master_cmd_begin(g_i2c_num, cmd, portMAX_DELAY), TAG, "i2c_master_cmd_begin");
    i2c_cmd_link_delete(cmd);
    raw_data->temp = (int16_t)(data[0] << 8 | data[1]);
    raw_data->accel_x = (int16_t)(data[2] << 8 | data[3]);
    raw_data->accel_y = (int16_t)(data[4] << 8 | data[5]);
    raw_data->accel_z = (int16_t)(data[6] << 8 | data[7]);
    raw_data->gyro_x = (int16_t)(data[8] << 8 | data[9]);
    raw_data->gyro_y = (int16_t)(data[10] << 8 | data[11]);
    raw_data->gyro_z = (int16_t)(data[12] << 8 | data[13]);
    return ESP_OK;
}

esp_err_t icm42670p_deinit(){
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    if(handle == NULL){
        return ESP_FAIL;
    }
    ESP_RETURN_ON_ERROR(i2c_master_start(handle), TAG, "i2c_master_start");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, g_address << 1 | I2C_MASTER_WRITE, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, 0x1F, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_write_byte(handle, 0x00, true), TAG, "i2c_master_write_byte");
    ESP_RETURN_ON_ERROR(i2c_master_stop(handle), TAG, "i2c_master_stop");
    ESP_RETURN_ON_ERROR(i2c_master_cmd_begin(g_i2c_num, handle, portMAX_DELAY), TAG, "i2c_master_cmd_begin");
    i2c_cmd_link_delete(handle);
    return ESP_OK;
}
