# ICM-42670-P driver for ESP-IDF components

## Guide

The ICM-42670-P is a high performance 6-axis MEMS MotionTracking device that combines a 3-axis gyroscope and a 3-axis accelerometer. It has a configurable host interface that supports I3CSM, I2C, and SPI serial communication, features up to 2.25 Kbytes FIFO and 2 programmable interrupts with ultra-low-power wake-on-motion support to minimize system power consumption. This library supports only I2C commmunication in polling mode.

## Use

Add this component in your ESP-IDF project and try example code.

```c
    icm42670p_init(BSP_I2C_NUM, 0);             //BSP_I2C_NUM driver has been installed before
    vTaskDelay(pdMS_TO_TICKS(45));              //ensure icm42670p is ready
    icm42670_raw_t data = {0};

    for( ;; ){
        icm42670p_get_raw_data(&data);          //get raw data in polling mode
        ESP_LOGI(TAG, "/*"
                      "%f, %f, %f, %f, %f, %f, %f"
                      "*/",
                 get_real_temperature(data.temp), get_real_accel(data.accel_x), get_real_accel(data.accel_y), get_real_accel(data.accel_y),
                 get_real_gyro(data.gyro_x), get_real_gyro(data.gyro_y), get_real_gyro(data.gyro_z));
        vTaskDelay(pdMS_TO_TICKS(10));
    }
```



## Result

You can use [Serial Studio](*https://github.com/Serial-Studio/Serial-Studio*) to draw real-time data in graph.

![image-20230612165340537](C:\Users\njduh\Documents\CLionProjects\freeos\components\icm42670p\assets\image-20230612165340537.png)
