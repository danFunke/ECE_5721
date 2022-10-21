#include "MKL25Z4.h"                    // Device header

#define SPKR_SHIFT   (0)
#define MASK(x) (1ul << (x))

// Standard delay function
static void delay(volatile unsigned int time_del)
{
    while (time_del--) {}

}

int main(void)
{
    // Assign clock to Port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    // Make pin GPIO
    PORTB->PCR[SPKR_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[SPKR_SHIFT] |= PORT_PCR_MUX(1);

    // Set port to outputs
    PTB->PDDR |= MASK(SPKR_SHIFT);
    
    // Turn on Speaker by clearing the port bit to zeros
    PTB->PDOR |= MASK(SPKR_SHIFT);
    
    while(1) {
        PTB->PTOR = MASK(SPKR_SHIFT);
        delay(2000);       

        
    }
}
