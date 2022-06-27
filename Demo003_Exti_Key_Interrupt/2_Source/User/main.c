#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"

//int main(void) {
//    
//    systick_config();
//	
//	
//	 /* initialize the LEDs and turn on LED1 */
//    gd_eval_led_init(LED1);
//    gd_eval_led_init(LED2);
//    gd_eval_led_on(LED1);

//    /* configure the tamper key */
//    gd_eval_key_init(KEY_TAMPER, KEY_MODE_EXTI);

//    while(1) {
//    }
//	

////    return 0;
//}


int main(void)
{
    /* initialize the LEDs and turn on LED1 */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    /* configure the tamper key */
    gd_eval_key_init(KEY_TAMPER, KEY_MODE_EXTI);

    while(1) {
	
    gd_eval_led_on(LED1);

	}
}