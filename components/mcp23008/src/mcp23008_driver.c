#include "esp_log.h"
#include "esp_err.h"
#include "driver/i2c.h"

#include "mcp23008_driver.h"

#define ACK_CHECK_EN                        0x1              /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS                       0x0              /*!< I2C master will not check ack from slave */
#define ACK_VAL                             0x0              /*!< I2C ack value */
#define NACK_VAL                            0x1              /*!< I2C nack value */
#define LAST_NACK_VAL                       0x2              /*!< I2C last_nack value */

typedef enum mcp23008_register {
    IODIR_REG      = 0x00,    //< IO Direction
    IPOL_REG       = 0x01,    //< Input Polarity
    GPINTEN_REG    = 0x02,    //< Interrupt-on-change Control
    DEFVAL_REG     = 0x03,    //< Default Compare for Interrupt-on-Change
    INTCON_REG     = 0x04,    //< Interrupt Control
    IOCON_REG      = 0x05,    //< Configuration
    GPPU_REG       = 0x06,    //< Pull-up configuration
    INTF_REG       = 0x07,    //< Interrupt Flag (Read-Only)
    INTCAP_REG     = 0x08,    //< Interrupt Capture (Read-Only)
    GPIO_REG       = 0x09,    //< Port
    OLAT_REG       = 0x0A     //< Output Latch
} mcp23008_register_t;

static uint8_t mcp23008_addr = 0x0;
static i2c_port_t device_port = I2C_NUM_0;

esp_err_t mcp23008_read_register(mcp23008_register_t reg, uint8_t* buff) {
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    // Set the address to the register
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, mcp23008_addr << 1 | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(device_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        return ret;
    }

    cmd = i2c_cmd_link_create();

    // Read the register that was previosuly set
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, mcp23008_addr << 1 | I2C_MASTER_READ, ACK_CHECK_EN);
    i2c_master_read(cmd, buff, sizeof(uint8_t), LAST_NACK_VAL);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(device_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t mcp23008_write_register(mcp23008_register_t reg, uint8_t buff) {
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (mcp23008_addr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, buff, ACK_CHECK_EN);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(device_port, cmd, 1000 / portTICK_RATE_MS);

    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t mcp23008_read_input(uint8_t* inputs) {
    return mcp23008_read_register(GPIO_REG, inputs);
}

esp_err_t mcp23008_write_output(uint8_t outputs) {
    return mcp23008_write_register(GPIO_REG, outputs);
}

esp_err_t mcp23008_init(i2c_port_t port, uint8_t addr, uint8_t io_dir) {
    mcp23008_addr = addr;
    device_port = port;

    mcp23008_write_register(IOCON_REG, (1 << 5)); // Disable sequential register writes.
    mcp23008_write_register(IODIR_REG, io_dir);   // Write out IO direction.

    return ESP_OK;
}
