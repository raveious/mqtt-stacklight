#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "driver/i2c.h"

#include "mcp23008_driver.h"

#define I2C_SDA_PIN       0
#define I2C_SCL_PIN       2

#define DEVICE_MASTER_NUM I2C_NUM_0

static esp_err_t i2c_init (void) {
    i2c_config_t config;

    config.mode = I2C_MODE_MASTER;

    config.sda_io_num = I2C_SDA_PIN;
    config.sda_pullup_en = 1;
    
    config.scl_io_num = I2C_SCL_PIN;
    config.scl_pullup_en = 1;

    // config.clk_stretch_tick = 300;

    ESP_ERROR_CHECK(i2c_driver_install(DEVICE_MASTER_NUM, config.mode));
    ESP_ERROR_CHECK(i2c_param_config(DEVICE_MASTER_NUM, &config));
    return ESP_OK;
}

static void i2c_task(void* arg) {
    ESP_ERROR_CHECK(i2c_init());

    ESP_ERROR_CHECK(mcp23008_init(DEVICE_MASTER_NUM, MCP23008_BASE_ADDR, 0x10));

    while(1) {

    }

    i2c_driver_delete(DEVICE_MASTER_NUM);
}

void app_main(void) {

    // Make a task just to monitor the I2C device.
    xTaskCreate(i2c_task, "i2c_task", 2048, NULL, 10, NULL);
}