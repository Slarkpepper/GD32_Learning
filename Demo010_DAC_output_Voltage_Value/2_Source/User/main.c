#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"
#include "led.h"

#define DAC_OUT_VAL     (0x7FF0)

void rcu_config(void);
void gpio_config(void);
void dac_config(void);

int main(void) {

	ledInit();
	rcu_config();
	gpio_config();
	systick_config();
	dac_config();
	ledFlash(2);

	while(1) {


	}	
	
}

void rcu_config() {
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_DAC);
}

void gpio_config() {
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_4);
}

void dac_config() {

	dac_deinit();
	dac_trigger_disable(DAC0);
	dac_wave_mode_config(DAC0, DAC_WAVE_DISABLE);
	dac_output_buffer_enable(DAC0);

	dac_enable(DAC0);
	dac_data_set(DAC0, DAC_ALIGN_12B_L, DAC_OUT_VAL);
}