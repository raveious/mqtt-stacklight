#include "esp_log.h"
#include "esp_err.h"
#include "driver/i2c.h"

#include "mcp23008_driver.h"

#define IODIR_REG        (0x00)    //< IO Direction
#define IPOL_REG         (0x01)    //< Input Polarity
#define GPINTEN_REG      (0x02)    //< Interrupt-on-change Control
#define DEFVAL_REG       (0x03)    //< Default Compare for Interrupt-on-Change
#define INTCON_REG       (0x04)    //< Interrupt Control
#define IOCON_REG        (0x05)    //< Configuration
#define GPPU_REG         (0x06)    //< Pull-up configuration
#define INTF_REG         (0x07)    //< Interrupt Flag (Read-Only)
#define INTCAP_REG       (0x08)    //< Interrupt Capture (Read-Only)
#define GPIO_REG         (0x09)    //< Port
#define OLAT_REG         (0x0A)    //< Output Latch

static uint8_t mcp23008_addr = 0x0;

esp_err_t mcp23008_read() {
    return ESP_OK;
}

esp_err_t mcp23008_write() {
    return ESP_OK;
}

esp_err_t mcp23008_init(uint8_t addr, uint8_t io_dir) {
    mcp23008_addr = addr;
    return ESP_OK;
}
