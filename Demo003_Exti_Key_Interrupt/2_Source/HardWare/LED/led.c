#include "led.h"

#include "gd32f4xx.h"
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
    
    while(1) {
        gpio_bit_set(GPIOD, GPIO_PIN_4);
        gpio_bit_reset(GPIOD, GPIO_PIN_5);
        gpio_bit_reset(GPIOG, GPIO_PIN_3);
        delay_1ms(1000);

        gpio_bit_reset(GPIOD, GPIO_PIN_4);
        gpio_bit_set(GPIOD, GPIO_PIN_5);
        gpio_bit_reset(GPIOG, GPIO_PIN_3);
        delay_1ms(1000);


        gpio_bit_reset(GPIOD, GPIO_PIN_4);
        gpio_bit_reset(GPIOD, GPIO_PIN_5);
        gpio_bit_set(GPIOG, GPIO_PIN_3);
        delay_1ms(1000);
    }

}
