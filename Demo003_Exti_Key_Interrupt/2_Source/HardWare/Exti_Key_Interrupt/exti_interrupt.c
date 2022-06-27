#include "exti_interrupt.h"
#include "gd32f4xx.h"
#include "systick.h"
void extiInterruptInit() {

    //LED2初始化
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_bit_reset(GPIOD, GPIO_PIN_5);

    //Tamper初始化
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13);

    led_flash(100);

    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_SYSCFG);

    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOC, GPIO_PUPD_NONE, GPIO_OSPEED_50MHZ, GPIO_PIN_13);

    nvic_irq_enable(EXTI10_15_IRQn, 2U, 0U);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOC, EXTI_SOURCE_PIN13);

    exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_flag_clear(EXTI_13);

    while(1) {
        
    }

}

static void led_flash(uint8_t times) {

    uint8_t i;
    for(i = 0; i < times; i++) {
        delay_1ms(500);
        gpio_bit_set(GPIOD, GPIO_PIN_5);
        delay_1ms(500);
        gpio_bit_reset(GPIOD, GPIO_PIN_5);
    }


}
