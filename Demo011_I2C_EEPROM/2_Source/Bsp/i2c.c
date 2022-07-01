#include "gd32f4xx.h"
#include "i2c.h"
#include <stdio.h>

void gpio_config(void) {

    rcu_periph_clock_enable(RCU_GPIOB);
   // rcu_periph_clock_enable(RCU_I2C0);

    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6);
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_7);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
}

void i2c_config(void)   {
    rcu_periph_clock_enable(RCU_I2C0);
    i2c_clock_config(I2C0, I2C0_SPEED, I2C_DTCY_2);
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_SLAVE_ADDRESS7);
    i2c_enable(I2C0);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
}
