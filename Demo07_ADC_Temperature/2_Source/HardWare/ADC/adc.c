#include "adc.h"
#include "gd32f4xx.h"

void rcu_config() {
    rcu_periph_clock_enable(RCU_ADC0);
    adc_clock_config(ADC_ADCCK_PCLK2_DIV4);
}

void adc_config() {

    adc_channel_length_config(ADC0, ADC_INSERTED_CHANNEL, 3);

    adc_inserted_channel_config(ADC0, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_480);
    adc_inserted_channel_config(ADC0, 1, ADC_CHANNEL_17, ADC_SAMPLETIME_480);
    adc_inserted_channel_config(ADC0, 2, ADC_CHANNEL_18, ADC_SAMPLETIME_480);

    adc_external_trigger_config(ADC0, ADC_INSERTED_CHANNEL, DISABLE);
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
    adc_channel_16_to_18(ADC_VBAT_CHANNEL_SWITCH, ENABLE);
    adc_channel_16_to_18(ADC_TEMP_VREF_CHANNEL_SWITCH, ENABLE);

    adc_enable(ADC0);
    adc_calibration_enable(ADC0);
}

