#include "adc.h"
#include "MKL25Z4.h"
#include <math.h>

#define ADC_POS (20)

void adc_init(void)
{
    // Enable clock to ADC and PORTE
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    // Configure Analog Input Pin
    PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);

    // Configure ADC
    ADC0->CFG1 =    ADC_CFG1_ADLPC_MASK     |   // Lower power configuration
                    ADC_CFG1_ADIV(0)        |   // clock rate = input clock   
                    ADC_CFG1_ADLSMP_MASK    |   // long sample time
                    ADC_CFG1_MODE(3)        |   // 16-bit conversion
                    ADC_CFG1_ADICLK(0);         // input clock = bus clock
    
    // Select default voltage reference pins
    ADC0->SC2 = ADC_SC2_REFSEL(0);
}

#include <stdint.h>

float adc_read_temperature(void)
{
    // Constants used in conversion
    static const float A1 = 3.354016e-03;
    static const float B1 = 3.349290e-04;
    static const float C1 = 3.683843e-06;
    static const float D1 = 7.050455e-07;
    static const float r_ref = 15.0;
    static const float r_bal = 5000.0;

    static float temp = 0;
    // Start conversion on channel 0
    ADC0->SC1[0] = 0x00;

    // Wait for conversion to finish
    while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)) {}

    // Read result; convert to floating point
    //float n = (float)ADC0->R[0];
    float n = (float)ADC0->R[0];

    float r_therm = r_bal * ((65535.0 / n) - 1);


    // Calculate temperature from transfer function
    temp =   A1 + 
            (B1 * (log(r_therm/r_ref))) + 
            (C1 * (log(r_therm/r_ref) * log(r_therm/r_ref))) + 
            (D1 * (log(r_therm/r_ref) * log(r_therm/r_ref) * log(r_therm/r_ref)));
    temp = (1 / temp) - 273 + 20;
    
    return temp;
}
