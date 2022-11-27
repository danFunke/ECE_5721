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

#include <stdint.h>
#include <MKL25Z4.h>
#include <math.h>

// Define constants
#define DAC_UPDATE_INTERVAL (5)
#define MIN_AMPLITUDE       (0)
#define MAX_AMPLITUDE       (9)

static const double pi = 3.14159;
static const double twoPi = 2 * 3.14159;

static int component_waveform_freqs[NUM_COMPONENT_WAVES] = {
    [DELTA_WAVE] = 4,
    [THETA_WAVE] = 8,
    [ALPHA_WAVE] = 12,
    [BETA_WAVE]  = 16
};

static int component_waveform_amps[NUM_COMPONENT_WAVES];

static int wave_time = 0;
static int wave_period = 1;

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

    // Calculate Longest waveform period in ms
    wave_period = ((1 / component_waveform_freqs[0]) * 1000);

    // Subscribe to tick event
    __disable_irq();
    event_subscribe(&system_tick_event, &tick_handler);
    __enable_irq();

    // Initialize DAC
    // TODO: FILL IN THIS SECTION
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
        // Reset wave value
        //double wave_value = 0;
        //for (int i = 0; i < NUM_COMPONENT_WAVES; ++i) {
				//	wave_value = wave_value + (component_waveform_amps[i] * sin(2 * pi * component_waveform_freqs[i] * (wave_time / 1000)));
					//wave_value = wave_value + 1;
				//}
			float wave_value = sin(twoPi * (wave_time / 1000));

        // Update DAC value
        //TODO: fill this part in
    }
	
	
	//float wave_value = sin(twoPi * (wave_time / 1000));

}
