#include "key_poiling.h"
#include "gd32f4xx.h"
#include "systick.h"

void keyInit() {

    rcu_periph_clock_enable(RCU_GPIOG);
	gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    gpio_bit_reset(GPIOG, GPIO_PIN_3);

    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4 | GPIO_PIN_5);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5);
    gpio_bit_reset(GPIOD, GPIO_PIN_4 | GPIO_PIN_5);
	
	
	rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_14);
    

    int key1_flag = 0;
    int key2_flag = 0;
    int key3_flag = 0;
    while(1) {
        //USER KEY
        if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 0) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 0) {
                gpio_bit_toggle(GPIOG, GPIO_PIN_3);
                key3_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 1) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 1) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_4);
                key3_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 2) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key3_flag == 2) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_5);
                key3_flag++;
            }
        }
        if(key3_flag == 3)  key3_flag = 0;




        //Temper
        if(RESET == gpio_input_bit_get(GPIOC, GPIO_PIN_13) && key2_flag == 0) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOC, GPIO_PIN_13) && key2_flag == 0) {
                gpio_bit_toggle(GPIOG, GPIO_PIN_3);
                key2_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOC, GPIO_PIN_13) && key2_flag == 1) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOC, GPIO_PIN_13) && key2_flag == 1) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_4);
                key2_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOC, GPIO_PIN_13) && key2_flag == 2) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOB, GPIO_PIN_14) && key2_flag == 2) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_5);
                key2_flag++;
            }
        }
        if(key2_flag == 3)  key2_flag = 0;


        //Wakeup
        if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key1_flag == 0) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key1_flag == 0) {
                gpio_bit_toggle(GPIOG, GPIO_PIN_3);
                key1_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key1_flag == 1) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key1_flag == 1) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_4);
                key1_flag++;
            }
        }
        if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key2_flag == 2) {
			delay_1ms(100);
            if(RESET == gpio_input_bit_get(GPIOA, GPIO_PIN_0) && key2_flag == 2) {
                gpio_bit_toggle(GPIOD, GPIO_PIN_5);
                key1_flag++;
            }
        }
        if(key1_flag == 3)  key1_flag = 0;

    }
}
