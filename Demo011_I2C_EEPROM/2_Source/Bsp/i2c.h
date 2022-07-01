#ifndef __I2C_H
#define __I2C_H

#include "gd32f4xx.h"
#define I2C0_SPEED          400000
#define I2C0_SLAVE_ADDRESS7 0xA0
#define I2C_PAGE_SIZE       8

void gpio_config(void);
void i2c_config(void);

#endif
