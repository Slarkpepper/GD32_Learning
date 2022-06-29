#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"
#include <stdio.h>
#include "led.h"

uint8_t tx_buffer[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
                       0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
                       0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F }; 

#define ARRAYNUM(arr_name)  (uint32_t)(sizeof(arr_name) / sizeof(*(arr_name)))
#define USART0_DATA_ADDRESS ((uint32_t) 0x40011004)					   

uint8_t rx_buffer [ARRAYNUM(tx_buffer)];
volatile ErrStatus transfer_status = ERROR;

ErrStatus memoryCompare(uint8_t* src, uint8_t* dst, uint16_t length);
void usart_dma_config(void);





int main(void) {


    systick_config();

    ledInit();

	nvic_irq_enable(USART0_IRQn, 0U, 0U);
	
	gd_eval_com_init(EVAL_COM0);
	
	usart_dma_config();
	
	dma_channel_enable(DMA1, DMA_CH7);
	dma_channel_enable(DMA1, DMA_CH2);
	usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
	usart_dma_receive_config(USART0, USART_DENR_ENABLE);
	
	ledFlash(3);
	
	while(RESET == dma_flag_get(DMA1, DMA_CH7, DMA_INTF_FTFIF)) {
	}
	while(RESET == dma_flag_get(DMA1, DMA_CH2, DMA_INTF_FTFIF)) {
	}
	
	transfer_status = memoryCompare(tx_buffer, rx_buffer, ARRAYNUM(tx_buffer));
	
	while(1) {
		if(SUCCESS == transfer_status) {
			gd_eval_led_on(LED1);
			delay_1ms(400);
			gd_eval_led_on(LED2);
			delay_1ms(400);
			gd_eval_led_on(LED3);
			delay_1ms(400);
			
			gd_eval_led_off(LED1);
			gd_eval_led_off(LED2);
			gd_eval_led_off(LED3);
			
		}
		else {
			ledFlash(3);
		}
	}
	
	
	
//    return 0;
}

void usart_dma_config(){
	
	dma_single_data_parameter_struct dma_init_struct;
    /* enable DMA1 */
    rcu_periph_clock_enable(RCU_DMA1);
    /* deinitialize DMA channel7(USART0 tx) */
    dma_deinit(DMA1, DMA_CH7);
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.memory0_addr = (uint32_t)tx_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.number = ARRAYNUM(tx_buffer);
    dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
    /* configure DMA mode */
    dma_circulation_disable(DMA1, DMA_CH7);
    dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
    
    dma_deinit(DMA1, DMA_CH2);
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.memory0_addr = (uint32_t)rx_buffer;
    dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
    /* configure DMA mode */
    dma_circulation_disable(DMA1, DMA_CH2);
    dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
}

ErrStatus memoryCompare(uint8_t* src, uint8_t* dst, uint16_t length) {
	while(length--) {
		if(*src++ != *dst++) {
			return ERROR;
		}
	}
	return SUCCESS;
}

int fputc(int ch, FILE *f) {
	usart_data_transmit(EVAL_COM0, (uint8_t)ch);
	while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
	return ch;
}