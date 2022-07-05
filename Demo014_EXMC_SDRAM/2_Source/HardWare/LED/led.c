#include "led.h"

#include "gd32f450z_eval.h"
#include "systick.h"

void ledInit(void) {

    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOG);

    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE, GPIO_PIN_4 | GPIO_PIN_5 );
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5);

    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);


    gpio_bit_reset(GPIOD, GPIO_PIN_4 | GPIO_PIN_5);
    gpio_bit_reset(GPIOG, GPIO_PIN_3);
}

void ledFlash(uint8_t times) {
	int i ;
	for(i = 0; i < times; i++) {
		gd_eval_led_on(LED1);
		gd_eval_led_on(LED2);
		gd_eval_led_on(LED3);
		delay_1ms(1000);
		gd_eval_led_off(LED1);
		gd_eval_led_off(LED2);
		gd_eval_led_off(LED3);
		delay_1ms(1000);
	}
}
