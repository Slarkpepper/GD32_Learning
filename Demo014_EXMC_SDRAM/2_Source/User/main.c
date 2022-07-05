#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "gd32f450z_eval.h"
#include "exmc_sdram.h"

#define BUFFERSIZE          ((uint32_t)0x4000)
#define WRITE_READ_ADDR     ((uint32_t)0X0000)

uint32_t writereadstatue = 0;
uint8_t tx_buffer[BUFFERSIZE];
uint8_t rx_buffer[BUFFERSIZE];


int main(void) {

    uint16_t i = 0;
    ErrStatus init_state;

    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);

    systick_config();
           
    gd_eval_com_init(EVAL_COM0);

    init_state = exmc_synchronous_dynamic_ram_init(EXMC_SDRAM_DEVICE0);

    if(ERROR == init_state) {
        printf("\r\nSDRAM INIT FAIL");
        while(1);
    }
    printf("\r\n SDRAM INIT SUCCESS");
    delay_1ms(1000);

    fill_buffer(tx_buffer, BUFFERSIZE, 0X0000);
    delay_1ms(1000);

    sdram_writebuffer_16(EXMC_SDRAM_DEVICE0,(uint16_t*)tx_buffer, WRITE_READ_ADDR, BUFFERSIZE / 2);

    printf("\r\nSDRAM write WANCHENG");
    delay_1ms(1000);

    sdram_readbuffer_16(EXMC_SDRAM_DEVICE0, (uint16_t*)rx_buffer, WRITE_READ_ADDR, BUFFERSIZE / 2);
    
    printf("\r\nsdram read WANCHENG");
    delay_1ms(1000);


    printf("data check");
    for(i = 0; i < BUFFERSIZE; i++) {
        if(rx_buffer[i] != tx_buffer[i]) {
            writereadstatue++;
            break;
        }
    }

    if(writereadstatue) {
        printf("\r\n SDRAM test FAILED");
        gd_eval_led_on(LED3);
        gd_eval_led_on(LED2);
    }
    else {
        printf("\r\nSDRAM test SUCCESSED");
        delay_1ms(1000);
        printf("\r\nTHE DATA IS:\r\n");
        delay_1ms(1000);
        for(i = 0; i < BUFFERSIZE; i++) {
            printf("%2x ", rx_buffer[i]);
            if(((i + 1) % 16) == 0) {
                printf("\r\n");
            }
        }
        gd_eval_led_on(LED1);
    }
    while (1);
}

int fputc(int ch, FILE *f) {
    usart_data_transmit(EVAL_COM0, (uint8_t) ch);
    while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
    return ch;
}
