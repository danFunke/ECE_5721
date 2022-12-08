#include "display.h"
#include "MKL25Z4.h"

#define MASK(x) (1ul << (x))

#define RED_POS     (18)
#define GREEN_POS   (19)
#define BLUE_POS    (1)

enum led_colors {
    RED_LED,
    GREEN_LED,
    BLUE_LED,
    NUM_LED_COLORS
};

enum color_names {
    WHITE,
    MAGENTA,
    RED,
    YELLOW,
    BLUE,
    GREEN,
    NUM_COLORS
};

static int color_thresholds[NUM_COLORS] = {
    [WHITE]     = 0x20D,
    [MAGENTA]   = 0x1E1,
    [RED]       = 0x1B5,
    [YELLOW]    = 0x189,
    [BLUE]      = 0x15D,
    [GREEN]     = 0x102
};

static int colors[NUM_COLORS][NUM_LED_COLORS] = {
    [WHITE]     = {[RED_LED]= 1, [GREEN_LED]= 1, [BLUE_LED]= 1},
    [MAGENTA]   = {[RED_LED]= 1, [GREEN_LED]= 0, [BLUE_LED]= 1},
    [RED]       = {[RED_LED]= 1, [GREEN_LED]= 0, [BLUE_LED]= 0},
    [YELLOW]    = {[RED_LED]= 1, [GREEN_LED]= 1, [BLUE_LED]= 0},
    [BLUE]      = {[RED_LED]= 0, [GREEN_LED]= 0, [BLUE_LED]= 1},
    [GREEN]     = {[RED_LED]= 0, [GREEN_LED]= 1, [BLUE_LED]= 0}
};

static void control_rgb_led(int red, int green, int blue)
{
    // Clear previous
    PTB->PSOR |= MASK(RED_POS) | MASK(GREEN_POS);
    PTD->PSOR |= MASK(BLUE_POS);

    // Set current
    PTB->PCOR |= (red << RED_POS) | (green << GREEN_POS);
    PTD->PCOR |= (blue << BLUE_POS);
}

void display_init(void)
{
    // Enable clock to PORTB and PORTD
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    // Set RBG pins as GPIO
    PORTB->PCR[RED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_POS] |= PORT_PCR_MUX(1);
    PORTB->PCR[GREEN_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_POS] |= PORT_PCR_MUX(1);
    PORTD->PCR[BLUE_POS] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_POS] |= PORT_PCR_MUX(1);

    // Set pins as outputs
    PTB->PDDR |= MASK(RED_POS) | MASK(GREEN_POS);
    PTD->PDDR |= MASK(BLUE_POS);

    // Initialize as off
    PTB->PSOR |= MASK(RED_POS) | MASK(GREEN_POS);
    PTD->PSOR |= MASK(BLUE_POS);
}

void display_range(int b)
{
    unsigned i;

    for (i = 0; i < NUM_COLORS; ++i) {
        if (b > color_thresholds[i]) {
            break;
        }
    }

    control_rgb_led(colors[i][RED_LED], colors[i][GREEN_LED], colors[i][BLUE_LED]);
}
