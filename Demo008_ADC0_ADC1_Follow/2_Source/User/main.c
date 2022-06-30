#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"

#include <stdio.h>

void gpio_config(void);
void rcu_config(void);
void dma_config(void);
void adc_config(void);
void timer_config(void);

uint32_t adc_value[2] = {0};

int main(void) {
	
	rcu_config();
	gpio_config();
	timer_config();
	dma_config();
	adc_config();
	
	
	gd_eval_com_init(EVAL_COM0);
	systick_config();
	

	
	while(1) {
		delay_1ms(2000);
		printf("adc_value[0] is %08x \r\n", adc_value[0]);
		printf("adc_value[1] is %08x \r\n", adc_value[1]);
		printf("\r\n");
	}
	
}



void gpio_config() {
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_3);
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_5);
}



void rcu_config() {
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_DMA1);
	rcu_periph_clock_enable(RCU_TIMER1);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	rcu_periph_clock_enable(RCU_ADC0);
	rcu_periph_clock_enable(RCU_ADC1);
	adc_clock_config(ADC_ADCCK_PCLK2_DIV8);
}







void dma_config() {

	dma_single_data_parameter_struct dma_single_data_parameter;

	dma_deinit(DMA1, DMA_CH0);
	dma_single_data_parameter.periph_addr = (uint32_t) (&ADC_SYNCDATA);
	dma_single_data_parameter.periph_inc = DMA_PERIPH_INCREASE_ENABLE;
	dma_single_data_parameter.memory0_addr = (uint32_t) (adc_value);
	dma_single_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_single_data_parameter.periph_memory_width = DMA_PERIPH_WIDTH_32BIT;
	dma_single_data_parameter.circular_mode = DMA_CIRCULAR_MODE_ENABLE;
	dma_single_data_parameter.direction = DMA_PERIPH_TO_MEMORY;
	dma_single_data_parameter.number = 2;
	dma_single_data_parameter.priority = DMA_PRIORITY_HIGH;
	
	dma_single_data_mode_init(DMA1, DMA_CH0, &dma_single_data_parameter);
	dma_channel_subperipheral_select(DMA1, DMA_CH0, DMA_SUBPERI0);
	dma_channel_enable(DMA1, DMA_CH0);
}




void adc_config() {

	adc_sync_mode_config(ADC_DAUL_REGULAL_FOLLOW_UP);
	adc_sync_dma_config(ADC_SYNC_DMA_MODE1);
	adc_sync_dma_request_after_last_enable();

	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
	adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);

	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);

	adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 2);
	adc_channel_length_config(ADC1, ADC_REGULAR_CHANNEL, 2);

	adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_13, ADC_SAMPLETIME_480);
	adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_15, ADC_SAMPLETIME_480);
	adc_regular_channel_config(ADC1, 0, ADC_CHANNEL_13, ADC_SAMPLETIME_480);
	adc_regular_channel_config(ADC1, 1, ADC_CHANNEL_15, ADC_SAMPLETIME_480);

	adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, EXTERNAL_TRIGGER_RISING);
	adc_external_trigger_config(ADC1, ADC_REGULAR_CHANNEL, EXTERNAL_TRIGGER_DISABLE);
	adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_T1_CH1);

	adc_enable(ADC0);
	adc_calibration_enable(ADC0);
	adc_enable(ADC1);
	adc_calibration_enable(ADC1);
}




void timer_config() {

	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	timer_initpara.prescaler 			= 19999;
	timer_initpara.alignedmode			= TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection		= TIMER_COUNTER_UP;
	timer_initpara.period				= 9999;
	timer_initpara.clockdivision		= TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter	= 0;
	timer_init(TIMER1, &timer_initpara);

	timer_ocintpara.ocpolarity 		= TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.ocnpolarity 	= TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.ocidlestate		= TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate	= TIMER_OCN_IDLE_STATE_LOW;
	timer_ocintpara.outputstate		= TIMER_CCXN_ENABLE;
	timer_ocintpara.outputnstate	= TIMER_CCXN_DISABLE;
	timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);
	
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 3999);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
	timer_enable(TIMER1);
}



int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM0, (uint8_t) ch);
    while (RESET == usart_flag_get(EVAL_COM0,USART_FLAG_TBE));
    return ch;
}

