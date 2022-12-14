#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dma.h"
#include "adc.h"

#include "MKL25Z4.h" 

#define MASK(x)			 (1UL << (x))

#define PI2 6.2832
#define VREF 3.3f

#define DELTA_LED   (5) //PTD5
#define THETA_LED   (0) //PTD0
#define ALPHA_LED   (2) //PTD2
#define BETA_LED    (3) //PTD3
#define INV_LED     (1) //PTD1

#define DELTA_INDEX 4    
#define THETA_INDEX	8
#define ALPHA_INDEX 12
#define BETA_INDEX	16
#define INV_INDEX   30

typedef enum
{
    DELTA_BAND = 0x00,
    THETA_BAND = 0x01,
    ALPHA_BAND = 0x02,
    BETA_BAND  = 0x03,
    INV_BAND   = 0x04

} freq_band_t;


volatile uint8_t m_calculate_dft = 0u;

static uint16_t adc_samples[DFT_SAMPLES]    = { 0x00u };
static float x[DFT_SAMPLES]                 = { 0x00u };
static float Xre[(DFT_SAMPLES / 2) + 1]     = { 0x00u };
static float Xim[(DFT_SAMPLES / 2) + 1]     = { 0x00u };
static float P[(DFT_SAMPLES / 2) + 1]       = { 0x00u };

static const int to_sin = 3*DFT_SAMPLES/4;

static const float W[64] = {
     1.00000f, 0.99518f, 0.98079f, 0.95694f, 0.92388f, 0.88192f, 0.83147f, 0.77301f,
     0.70711f, 0.63439f, 0.55557f, 0.47139f, 0.38268f, 0.29028f, 0.19509f, 0.09801f,
    -0.00000f,-0.09802f,-0.19509f,-0.29029f,-0.38269f,-0.47140f,-0.55557f,-0.63440f,
    -0.70711f,-0.77301f,-0.83147f,-0.88192f,-0.92388f,-0.95694f,-0.98079f,-0.99519f,
    -1.00000f,-0.99518f,-0.98078f,-0.95694f,-0.92388f,-0.88192f,-0.83146f,-0.77300f,
    -0.70710f,-0.63439f,-0.55556f,-0.47139f,-0.38267f,-0.29027f,-0.19508f,-0.09801f,
     0.00001f, 0.09803f, 0.19510f, 0.29030f, 0.38269f, 0.47141f, 0.55558f, 0.63440f,
     0.70712f, 0.77302f, 0.83148f, 0.88193f, 0.92388f, 0.95694f, 0.98079f, 0.99519f
};

static void gpio_init(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; // enable clock to Port D
	
	// select GPIO
	PORTD->PCR[DELTA_LED]   &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[DELTA_LED]   |= PORT_PCR_MUX(1);
	PORTD->PCR[THETA_LED]   &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[THETA_LED]   |= PORT_PCR_MUX(1);
	PORTD->PCR[ALPHA_LED]   &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[ALPHA_LED]   |= PORT_PCR_MUX(1);
	PORTD->PCR[BETA_LED]    &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BETA_LED]    |= PORT_PCR_MUX(1);
    PORTD->PCR[INV_LED]     &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[INV_LED]     |= PORT_PCR_MUX(1);
	
	PTD->PDDR |= MASK(DELTA_LED); // set button to output
	PTD->PDDR |= MASK(THETA_LED);
	PTD->PDDR |= MASK(ALPHA_LED);
	PTD->PDDR |= MASK(BETA_LED);
    PTD->PDDR |= MASK(INV_LED);
}

static void samples_conversion(float adc_res)
{
    uint8_t i = 0;

    for (i; i < DFT_SAMPLES; i++)
    {
        float temp = 0.0f;
    
        //transfer function
        temp = (float)adc_samples[i] - 0.5f;
        temp /= adc_res;
        temp *= VREF;

        x[i] = temp;
    }
}

static void simple_dft(void)
{
    uint8_t k = 0; //frequency domain index
    uint8_t n = 0; //time domain index

    int a, b;

    for (k=0 ; k<=DFT_SAMPLES/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; 
				b = to_sin;

        for (n=0 ; n<DFT_SAMPLES ; ++n)
        {
            Xre[k] += x[n] * W[a%DFT_SAMPLES];
            Xim[k] -= x[n] * W[b%DFT_SAMPLES];
            a += k; b += k;
        }
        
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
    }
}

static void power_comparison(freq_band_t* max_freq_band)
{
    uint8_t k = 1; // 0th index of the DFT power array is the DC component, start at 1st
    uint8_t i = 0;

    /* 0 Delta | 1 Theta | 2 Alpha | 3 Beta | 4 Inv */
    float power_arr[5] = {0.0f};
		float max_power = 0.0f;

    for (k; k <= DELTA_INDEX; k++)
    {
        power_arr[DELTA_BAND] += P[k];
    }
    for (k; k <= THETA_INDEX; k++)
    {
        power_arr[THETA_BAND] += P[k];
    }
    for (k; k <= ALPHA_INDEX; k++)
    {
        power_arr[ALPHA_BAND] += P[k];
    }
    for (k; k <= BETA_INDEX; k++)
    {
        power_arr[BETA_BAND] += P[k];
    }
    for (k; k <= INV_INDEX; k++)
    {
        power_arr[INV_BAND] += P[k];
    }

    max_power = power_arr[DELTA_BAND];

    for (i = 1; i <= 5; i++)
    {
        if (power_arr[i] > max_power)
        {
            *max_freq_band = (freq_band_t)i;
        }
    }
}

static void output_leds(freq_band_t band)
{
    switch(band)
    {
        case DELTA_BAND:
        {
            PTD->PSOR = MASK(DELTA_LED);
            PTD->PCOR = MASK(THETA_LED) | MASK(ALPHA_LED) | MASK(BETA_LED) | MASK(INV_LED);
            break;
        }
        case THETA_BAND:
        {
            PTD->PSOR = MASK(THETA_LED);
            PTD->PCOR = MASK(DELTA_LED) | MASK(ALPHA_LED) | MASK(BETA_LED) | MASK(INV_LED);
            break;
        }
        case ALPHA_BAND:
        {
            PTD->PSOR = MASK(ALPHA_LED);
            PTD->PCOR = MASK(DELTA_LED) | MASK(THETA_LED) | MASK(BETA_LED) | MASK(INV_LED);
            break;
        }
        case BETA_BAND:
        {
            PTD->PSOR = MASK(BETA_LED);
            PTD->PCOR = MASK(DELTA_LED) | MASK(THETA_LED) | MASK(ALPHA_LED) | MASK(INV_LED);
            break;
        }
        case INV_BAND:
        {
            PTD->PSOR = MASK(INV_LED);
            PTD->PCOR = MASK(DELTA_LED) | MASK(THETA_LED) | MASK(ALPHA_LED) | MASK(BETA_LED);
            break;
        }
        default:
        {
            break;
        }
    }
}

static void initialization(void)
{
    adc_init();
    systick_init();
    // dma_init(adc_samples);
    gpio_init();
}

int main(void)
{
    freq_band_t max_band = DELTA_BAND;
	
    float adc_res = pow(2, 16);

    initialization();

    while(1)
    {
        if (m_calculate_dft == 0x01) //this means that there are new samples and the power needs to be calculated
        {
				    m_calculate_dft = 0x00;
            retrieve_samples(adc_samples);
            samples_conversion(adc_res);
            simple_dft(); 
            power_comparison(&max_band); 
        }

        output_leds(max_band); //TODO add minor delay?
        
    }
}
