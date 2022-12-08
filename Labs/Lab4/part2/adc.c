#include "adc.h"
#include "MKL25Z4.h"

#define IR_PHOTOTRANSISTOR_CHANNEL  (8)
#define NUM_SAMPLES_TO_AVG          (10)

void adc_init(void)
{
    // Enable clock to ADC0
    SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
    
    // Configure ADC
    ADC0->CFG1 =    ADC_CFG1_ADLPC_MASK     |   // Enable low-power configuration
                    ADC_CFG1_ADIV(0)        |   // Set clock divide ratio to 1
                    ADC_CFG1_ADLSMP_MASK    |   // Long sample time
                    ADC_CFG1_MODE(3)        |   // 16-bit conversion mode
                    ADC_CFG1_ADICLK(0);         // Input clock = bus clock

    // Select default voltage reference pins
    ADC0->SC2 = ADC_SC2_REFSEL(0);
}

unsigned adc_measure_IR(void)
{
    volatile unsigned res = 0;

    // Start Conversion
    ADC0->SC1[0] = IR_PHOTOTRANSISTOR_CHANNEL;

    // Wait until conversion is complete
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)) {}

    res = ADC0->R[0];

    // Complement result since voltage falls with increasing IR level
    return (0xffff - res);
}
