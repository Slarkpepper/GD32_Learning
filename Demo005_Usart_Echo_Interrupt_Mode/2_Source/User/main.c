#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"
#include "led.h"
#include <stdio.h>

int main(void) {


    systick_config();

//	ledInit();
//	
//	ledFlash(3);
//	
//	gd_eval_com_init(EVAL_COM0);
//	gd_eval_key_init(KEY_TAMPER, KEY_MODE_GPIO);
//	
//	printf("\r\nUSART BEGIN!!!!!!!!!!!\r\n");
//	
//	while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TC)) {
//	}
//	while(1) {
//		if(RESET == gd_eval_key_state_get(KEY_TAMPER)) {
//			delay_1ms(100);
//			if(RESET == gd_eval_key_state_get(KEY_TAMPER)) {
//				gd_eval_led_on(LED1);
//				printf("\r\n Hello Slarkpepper \r\n");
//				while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TC)){
//				}
//			}
//			else {
//				gd_eval_led_off(LED1);
//			}
//		}
//		else {
//			gd_eval_led_off(LED1);
//		}
//		
//	}
}

int fputc(int ch, FILE *f) {
	usart_data_transmit(EVAL_COM0, (uint8_t)ch);
	while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
	return ch;
}


