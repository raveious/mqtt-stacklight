
#pragma once

#include "esp_err.h"

#define MCP23008_BASE_ADDR (0x20)

esp_err_t mcp23008_init(uint8_t addr, uint8_t io_dir);
