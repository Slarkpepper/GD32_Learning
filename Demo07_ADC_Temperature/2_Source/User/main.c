#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"
#include "led.h"
#include "adc.h"
#include <stdio.h>

float temperature = 0, vref_value = 0, battery_value = 0;

int main(void) {

	rcu_config();
	adc_config();
	systick_config();
	gd_eval_com_init(EVAL_COM0);

	ledInit();
	ledFlash(3);

	while(1) {
		adc_software_trigger_enable(ADC0, ADC_INSERTED_CHANNEL);
		delay_1ms(2000);
		temperature = (1.42-ADC_IDATA0(ADC0)*3.3/4096)*1000/4.35+25;
        vref_value = (ADC_IDATA1(ADC0)*3.3/4096);
        battery_value = (ADC_IDATA2(ADC0)*4*3.3/4096);
	
		printf("the temperature is %2.0f\r\n", temperature);
		printf("the vref_value is %3.0f\r\n", vref_value);
		printf("the battery_value is %3.0f\r\n", battery_value);
        printf(" \r\n");
		delay_1ms(1000);
		
	}
}


int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM0, (uint8_t) ch);
    while (RESET == usart_flag_get(EVAL_COM0,USART_FLAG_TBE));
    return ch;
}




