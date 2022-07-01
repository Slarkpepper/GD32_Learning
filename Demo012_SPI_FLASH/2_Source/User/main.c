#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"
#include "led.h"
#include "i2c.h"
#include "at24cxx.h"
#include <stdio.h>

uint8_t count = 0;
void led_turn_on(uint8_t led_number);
int main(void) {

	systick_config();
	ledInit();
	gd_eval_com_init(EVAL_COM0);
	printf("GD32450Z-EVAL I2C-24C02 configured....\n\r");

	gpio_config();
	i2c_config();
	i2c_eeprom_init();

	printf("THE I2C0 IS HARDWARE INTERFACE");
	printf("\r\n THE SPEED IS %d", I2C0_SPEED);

	if(I2C_OK == i2c_24c02_test()) {
		while(1) {
			gd_eval_led_off(LED1);
			gd_eval_led_off(LED2);
			gd_eval_led_off(LED3);

			led_turn_on(count % 3);
			count++;

			if(count >= 3) {
				count = 0;
			} 
			delay_1ms(500);
		}
	}
	gd_eval_led_on(LED1);
	gd_eval_led_on(LED2);
	gd_eval_led_on(LED3);
	
	while(1) {


	}
}

void led_turn_on(uint8_t led_number)
{
    switch(led_number) {
    case 0:
        gd_eval_led_on(LED1);
        break;
    case 1:
        gd_eval_led_on(LED2);
        break;
    case 2:
        gd_eval_led_on(LED3);
        break;
    default:
        gd_eval_led_on(LED1);
        gd_eval_led_on(LED2);
        gd_eval_led_on(LED3);
        break;
    }
}


int fputc(int ch, FILE *F){
	usart_data_transmit(USART0, (uint8_t) ch);
	while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
	return ch;
}
