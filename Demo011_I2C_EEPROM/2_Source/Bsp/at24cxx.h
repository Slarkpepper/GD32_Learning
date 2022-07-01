#ifndef __AT24CXX_H
#define __AT24CXX_H
#include "gd32f4xx.h"

#define I2C_OK      0
#define I2C_FAILED  1

#define EEP_FIRST_PAGE 0x00

uint8_t i2c_24c02_test(void);

void i2c_eeprom_init(void);
void eeprom_byte_write(uint8_t *p_buffer, uint8_t write_address);
void eeprom_page_write(uint8_t *p_buffer, uint8_t write_address, uint8_t number_of_byte);
void eeprom_buffer_write(uint8_t *p_buffer, uint8_t write_address, uint16_t number_of_byte);
void eeprom_buffer_read(uint8_t *p_buffer, uint8_t read_address, uint16_t number_of_byte);
void eeprom_wait_standby_state(void);

#endif
