
#pragma once

#include "esp_err.h"
#include "driver/i2c.h"

#define MCP23008_BASE_ADDR (0x20)

esp_err_t mcp23008_init(i2c_port_t port, uint8_t addr, uint8_t io_dir);
