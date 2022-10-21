#include "MKL25Z4.h"
#include <stdbool.h>

#define GREEN_LED_SHIFT     (0)
#define RED_LED_SHIFT       (1)
#define YELLOW_LED_SHIFT    (2)
#define BLUE_LED_SHIFT      (3)
#define ETS_SHIFT           (1)
#define FLS_SHIFT           (2)
#define OFS_SHIFT           (9)
#define MASK(x) (1ul << (x))

enum state {
    STATE_START,
    STATE_TANK_EMPTY,
    STATE_WATER_IN_TANK,
    STATE_TANK_FULL,
    STATE_TANK_OVERFLOW
};

// Sensor states
static bool ETS; // Empty Tank Sensor
static bool FLS; // Full Tank Sensor
static bool OFS; // Over Flow Sensor

// System state
static int current_state = STATE_START;

static void init_output(void)
{
    // Assign clock to Port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    // Make Port B Pins(0:3) GPIO
    PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
    PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
    PORTB->PCR[YELLOW_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[YELLOW_LED_SHIFT] |= PORT_PCR_MUX(1);
    PORTB->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);

    // Set Port B Pins(0:3) as outputs
    PTB->PDDR |= MASK(GREEN_LED_SHIFT) | MASK(RED_LED_SHIFT) | MASK(YELLOW_LED_SHIFT) | MASK(BLUE_LED_SHIFT);
}

static void init_sensors(void)
{
    // Assign clock to Port C
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Make Port C Pins(1,2,9) GPIO
    PORTC->PCR[ETS_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTC->PCR[ETS_SHIFT] |= PORT_PCR_MUX(1);
    PORTC->PCR[FLS_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTC->PCR[FLS_SHIFT] |= PORT_PCR_MUX(1);
    PORTC->PCR[OFS_SHIFT] &= ~PORT_PCR_MUX_MASK;
    PORTC->PCR[OFS_SHIFT] |= PORT_PCR_MUX(1);

    // Set Port C Pins (1,2,9) as inputs
    PTC->PDDR &= ~(MASK(ETS_SHIFT) | MASK(FLS_SHIFT) | MASK(OFS_SHIFT));
}

static void init_system(void)
{
    // Set up GPIO ports
    init_output();
    init_sensors();

    // Set initial output states
    // PTB->PCOR |= MASK(BLUE_LED_SHIFT);
    // PTB->PSOR |= MASK(GREEN_LED_SHIFT)| MASK(RED_LED_SHIFT) | MASK(YELLOW_LED_SHIFT);

    // Set initial sensor states
    ETS = false;
    FLS = false;
    OFS = false;
}

static void update_sensors(void)
{
    if (!(PTC->PDIR & MASK(ETS_SHIFT))) {
        ETS = !ETS;
    }

    if (!(PTC->PDIR & MASK(FLS_SHIFT))) {
        FLS = !FLS;
    }

    if (!(PTC->PDIR & MASK(OFS_SHIFT))) {
        OFS = !OFS;
    }
}

static void update_output(void)
{
    switch(current_state) {
        case STATE_START:
            //  All LEDs = OFF
            PTB->PSOR |= MASK(GREEN_LED_SHIFT)| MASK(BLUE_LED_SHIFT) | MASK(YELLOW_LED_SHIFT) | MASK(RED_LED_SHIFT);
            break;
        case STATE_TANK_EMPTY:
            // Blue LED = ON, others = OFF
            PTB->PCOR |= MASK(BLUE_LED_SHIFT);
            PTB->PSOR |= MASK(GREEN_LED_SHIFT)| MASK(YELLOW_LED_SHIFT) | MASK(RED_LED_SHIFT);
            break;
        case STATE_WATER_IN_TANK:
            // Green and Blue LEDs = ON, Yellow and Red LEDs = OFF
            PTB->PCOR |= MASK(BLUE_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
            PTB->PSOR |= MASK(YELLOW_LED_SHIFT) | MASK(RED_LED_SHIFT);
            break;
        case STATE_TANK_FULL:
            // Yellow and Blue LEDs = ON, Green and Red LEDs = OFF
            PTB->PCOR |= MASK(BLUE_LED_SHIFT) | MASK(YELLOW_LED_SHIFT);
            PTB->PSOR |= MASK(GREEN_LED_SHIFT)| MASK(RED_LED_SHIFT);
            break;
        case STATE_TANK_OVERFLOW:
            // Red LED ON, others OFF
            PTB->PCOR |= MASK(RED_LED_SHIFT);
            PTB->PSOR |= MASK(GREEN_LED_SHIFT)| MASK(BLUE_LED_SHIFT) | MASK(YELLOW_LED_SHIFT);
            break;
    }
}

static void update_state(void)
{
    switch(current_state) {
        case STATE_START:
            if (ETS) {
                current_state = STATE_TANK_EMPTY;
            } else {
                current_state = STATE_START;
            }
            break;
        case STATE_TANK_EMPTY:
            if (ETS) {
                current_state = STATE_TANK_EMPTY;
            } else {
                current_state = STATE_WATER_IN_TANK;
            }
            break;
        case STATE_WATER_IN_TANK:
                if (ETS) {
                    current_state = STATE_TANK_EMPTY;
                } else if (FLS) {
                    current_state = STATE_TANK_FULL;
                } else {
                    current_state = STATE_WATER_IN_TANK;
                }
            break;
        case STATE_TANK_FULL:
            if (!FLS) {
                current_state = STATE_WATER_IN_TANK;
            } else if (OFS) {
                current_state = STATE_TANK_OVERFLOW;
            } else {
                current_state = STATE_TANK_FULL;
            }
            break;
        case STATE_TANK_OVERFLOW:
            if (!OFS) {
                current_state = STATE_TANK_FULL;
            } else {
                current_state = STATE_TANK_OVERFLOW;
            }
            break;
    }
}

int main(void)
{
    init_system();

    while(1)
    {
        update_sensors();
        update_state();
        update_output();
    }
}
