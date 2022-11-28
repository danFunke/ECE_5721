#include "dma.h"

#include "MKL25Z4.h" 

extern uint8_t m_calculate_dft;
volatile uint16_t dma_count = 0u;

void dma_init(uint16_t* dest)
{
    //enable clock to DMA
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

    //disable DMA channel to allow for cfg
    DMAMUX0->CHCFG[0] = 0;

    //generate DMA interrupt when done
    //increment source, transfer words (16 bits)
    //enable peripheral request
    DMA0->DMA[0].DCR |= DMA_DCR_EINT_MASK | 
                        DMA_DCR_DINC_MASK | 
                        DMA_DCR_SSIZE(2) | 
                        DMA_DCR_DSIZE(2) | 
                        DMA_DCR_ERQ_MASK |
                        DMA_DCR_CS_MASK;

    
    DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) &ADC0->R[0]);
    DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) dest);

    DMA0->DMA[0].DAR |= DMA_DSR_BCR_BCR((uint16_t)(125 * 2));
    DMA0->DMA[0].DAR |= DMA_DSR_BCR_DONE_MASK;

    //set DMA MUX to use ADC interrupt as trigger
    DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_TRIG_MASK;
    DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_SOURCE(40); 
		
    DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
		
		//configure interrupts
    NVIC_SetPriority(DMA0_IRQn, 2); //TODO should the priority be higher
    NVIC_ClearPendingIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);

}

void DMA0_IRQHandler(void)
{
    DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
    dma_count++;
    if (dma_count >= 250)
    {
        m_calculate_dft = 0x01;
        dma_count = 0x0000;
    }
}
