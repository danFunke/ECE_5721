/**
 * @file waveform_generator.c
 * @author D. Funke
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 */

#include "waveform_generator.h"
#include "event.h"
#include "SysTick.h"
#include "system_time.h"
#include "sin_tables.h"

#include <stdint.h>
#include <MKL25Z4.h>

// Define constants
#define DAC_UPDATE_INTERVAL (5)
#define MIN_AMPLITUDE       (0)
#define MAX_AMPLITUDE       (9)
#define DAC_POS             (30)

static int component_waveform_amps[NUM_COMPONENT_WAVES];

static int wave_time = 0;
static const int wave_period = 250;

/**
 * @brief   An event handler to update the time variable used in the sin function
 *          with every SysTick
 * 
 * @param evt   Unused 
 * @param ctx   Unused 
 */
static void wave_time_update(event_t *evt, void *ctx)
{
    (void)evt;
    (void)ctx;

    wave_time++;
    wave_time %= wave_period;
}

static event_handler_t tick_handler = EVENT_HANDLER_INIT(wave_time_update);

void waveform_generator_init(void)
{
    // Initialize all amplitudes to 0
    for (int i = 0; i < NUM_COMPONENT_WAVES; ++i) {
        component_waveform_amps[i] = 0;
    }

    // Subscribe to tick event
    __disable_irq();
    event_subscribe(&system_tick_event, &tick_handler);
    __enable_irq();

    // Initialize DAC
    SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Select Analog for pin
    PORTE->PCR[DAC_POS] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[DAC_POS] |= PORT_PCR_MUX(0);

    // Disable buffer mode
    DAC0->C1 = 0;
    DAC0->C2 = 0;

    // Enable DAC and select VDDA as reference voltage
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

void waveform_generator_increment_amplitude(int waveform_index)
{
    if (waveform_index < NUM_COMPONENT_WAVES) {
        if (component_waveform_amps[waveform_index] < MAX_AMPLITUDE) {
            component_waveform_amps[waveform_index]++;
        }
    }
}

void waveform_generator_decrement_amplitude(int waveform_index)
{
    if (waveform_index < NUM_COMPONENT_WAVES) {
        if (component_waveform_amps[waveform_index] > MIN_AMPLITUDE) {
            component_waveform_amps[waveform_index]--;
        }
    }
}

int waveform_generator_get_amplitude(int waveform_index)
{
    return component_waveform_amps[waveform_index];
}

void waveform_generator_update(void)
{
	
    static uint32_t last_time = 0;
    uint32_t current_time = system_time_get_ms();
	
    if ((current_time - last_time) >= DAC_UPDATE_INTERVAL) {
        // Initilize wave value to 0
        float wave_value = 0;

        // Construct composite wave signal
        // Scale output signal by user input amplitudes; each component waveform has max amplitude of 0.4 V
        for (int i = 0; i < NUM_COMPONENT_WAVES; ++i) {
            wave_value = wave_value + (((component_waveform_amps[i] + 1) * 0.4) * sin_tables_get_value(i, wave_time));
        }

        // Update DAC value
        uint16_t dac_value = (wave_value * 1241) - 1; // NOTE: 1241 = 4096 / 3.3
        DAC0->DAT[0].DATL = DAC_DATL_DATA0(dac_value);
        DAC0->DAT[0].DATH = DAC_DATH_DATA1(dac_value >> 8);
    }
}
