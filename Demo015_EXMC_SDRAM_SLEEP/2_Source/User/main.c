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

void system_clock_configuration(void);


int main(void) {
	
	exmc_sdram_command_parameter_struct sdram_command_init_struct;
	uint16_t i = 0;
	ErrStatus initstate;

	gd_eval_led_init(LED1);
	gd_eval_led_init(LED2);
	gd_eval_led_init(LED3);

	rcu_periph_clock_enable(RCU_PMU);

	gd_eval_key_init(KEY_USER, KEY_MODE_EXTI);

	systick_config();

	gd_eval_com_init(EVAL_COM0);

	initstate = exmc_synchronous_dynamic_ram_init(EXMC_SDRAM_DEVICE0);
	
	if(ERROR == initstate) {
		printf("\r\n SDRAM INIT FAILED!");
		while(1);
	}

	printf("\r\n sdram init !");
	delay_1ms(1000);

	fill_buffer(tx_buffer, BUFFERSIZE, 0X0000);

	sdram_writebuffer_16(EXMC_SDRAM_DEVICE0, (uint16_t *)tx_buffer, WRITE_READ_ADDR, BUFFERSIZE / 2);

	printf("\r\n SDRAM write data completed!");
	delay_1ms(1000);

	sdram_command_init_struct.command = EXMC_SDRAM_SELF_REFRESH;
    sdram_command_init_struct.bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_1_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;

	while(exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) == SET);
    exmc_sdram_command_config(&sdram_command_init_struct);
	
    while(exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) == SET);
	
    while(exmc_sdram_bankstatus_get(EXMC_SDRAM_DEVICE0) != EXMC_SDRAM_DEVICE_SELF_REFRESH);

    printf("\r\nEnter deepsleep mode!");
    delay_1ms(1000);
    printf("\r\nPress the user key to wakeup the MCU!\r\n");
    delay_1ms(1000);

    /* enter deepsleep mode, light on LED2 */
    gd_eval_led_on(LED2);
	printf("\r\n=.= 1\r\n");
	pmu_to_deepsleepmode(PMU_LDO_NORMAL, PMU_LOWDRIVER_DISABLE, WFI_CMD);
	printf("\r\nQAQ\r\n");
    gd_eval_led_off(LED2);

	
    /* reinitialize the system clock */
    system_clock_configuration();

    printf("\r\nUser key has been pressed!");
    delay_1ms(1000);

    /* return normal mode */
    sdram_command_init_struct.command = EXMC_SDRAM_NORMAL_OPERATION;
    sdram_command_init_struct.bank_select = EXMC_SDRAM_DEVICE0;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    sdram_command_init_struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    while(exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET)
    {
        exmc_sdram_command_config(&sdram_command_init_struct);
    }
    /* wait until the SDRAM controller is ready */
    while(exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET)
	{
		while(exmc_sdram_bankstatus_get(EXMC_SDRAM_DEVICE0) != EXMC_SDRAM_DEVICE_NORMAL);
	}
	

    printf("\r\nSDRAM read data completed!");
    delay_1ms(1000);


	sdram_readbuffer_16(EXMC_SDRAM_DEVICE0, (uint16_t *) rx_buffer, WRITE_READ_ADDR, BUFFERSIZE / 2);

	printf("\r\n 检查数据！");
	delay_1ms(1000);


	for (i = 0; i < BUFFERSIZE; i++)
	{
		if(rx_buffer[i] == tx_buffer[i]) {
			writereadstatue++;
			break;
		}
	}

	if(writereadstatue) {
		printf("\r\n TEST FAILED");
		gd_eval_led_on(LED3);
	}
	else{
		printf("\r\n TEST SUCCEED");
		delay_1ms(1000);
		printf("\r\n print data:\r\n");
		for(i = 0; i < BUFFERSIZE; i++) {
			printf("%2x", rx_buffer[i]);
			if(((i + 1) % 16) == 0){
				printf("\r\n");
			}
		}
		gd_eval_led_on(LED1);
		gd_eval_led_on(LED2);
	}
	while (1);


}
void system_clock_configuration(void) {

	uint32_t timeout = 0U;
	uint32_t stab_flag = 0U;

	RCU_CTL |= RCU_CTL_HXTALEN;
	do{
		timeout++;
		stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
	}while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

	if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
		while (1);		
	}

	RCU_APB1EN |= RCU_APB1EN_PMUEN;
	PMU_CTL |= PMU_CTL_LDOVS;
	 
	RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
	RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
	RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

	RCU_PLL = (25U | (400U << 6U) | (((2U >> 1U) - 1U) << 16U) |
			  (RCU_PLLSRC_HXTAL) | (9U << 24U));

	RCU_CTL |= RCU_CTL_PLLEN;

	while (0U == (RCU_CTL & RCU_CTL_PLLSTB));

	PMU_CTL |= PMU_CTL_HDEN;
	while (0U == (PMU_CS & PMU_CS_HDRF));

	RCU_CFG0 &= ~RCU_CFG0_SCS;
	RCU_CFG0 |= RCU_CKSYSSRC_PLLP;
	while(0u == (RCU_CFG0 & RCU_SCSS_PLLP));
}


int fputc(int ch, FILE *f) {
	usart_data_transmit(EVAL_COM0, (uint8_t) ch);
	while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
	return ch;
}

