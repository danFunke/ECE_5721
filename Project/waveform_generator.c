/**
 * @file waveform_generator.h
 * @author D. Funke
 * @brief   Module to generate a complex sinusoidal waveform with high
 *          frequency noise contamination
 * 
 */

#include "waveform_generator.h"

#include <math.h>
#include <stdint.h>

#include "event.h"
#include "system_time.h"

#define DAC_UPDATE_INTERVAL (3)
#define MIN_WAVEFORM_AMP    (0)
#define MAX_WAVEFORM_AMP    (10)
const double pi = 3.141592;

static int component_waveform_freqs[NUM_COMPONENT_WAVES] = {
    [DELTA_WAVE] = 3,
    [THETA_WAVE] = 7,
    [ALPHA_WAVE] = 11,
    [BETA_WAVE]  = 17
};

static int component_waveform_amps[NUM_COMPONENT_WAVES] = {
    [DELTA_WAVE] = 0,
    [THETA_WAVE] = 0,
    [ALPHA_WAVE] = 0,
    [BETA_WAVE]  = 0
};

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
    // Subscribe to tick event
    __disable_irq();
    wave_period = ((1 / component_waveform_freqs[0]) * 1000);
    event_subscribe(&SysTick_event, &tick_handler);
    __enable_irq();

    // Initialize DAC
}

void waveform_generator_increment_amplitude(int target_waveform)
{
    if (target_waveform < NUM_COMPONENT_WAVES) {
        if (component_waveform_amps[target_waveform] < MAX_WAVEFORM_AMP) {
            component_waveform_amps[target_waveform]++;
        }
    }
}

void waveform_generator_decrement_amplitude(int target_waveform)
{
    if (target_waveform < NUM_COMPONENT_WAVES) {
        if (component_waveform_amps[target_waveform] > MIN_WAVEFORM_AMP) {
            component_waveform_amps[target_waveform]--;
        }
    }
}

int waveform_generator_get_amplitude(int target_waveform)
{
    // Initialize return variable
    int ret = -1;

    if (target_waveform > NUM_COMPONENT_WAVES) {
        ret = component_waveform_amps[target_waveform];
    }

    return -1;
}

void waveform_generator_update(void)
{
    static uint32_t last_time = 0;
    uint32_t current_time = system_time_get_ms();
    if ((current_time - last_time) >= DAC_UPDATE_INTERVAL) {
        // Reset wave value
        double wave_value = 0;
        for (int i = 0; i < NUM_COMPONENT_WAVES; ++i) {
            wave_value = wave_value + (component_waveform_amp[i] * sin(2 * pi * component_waveform_freqs[i]));
        }

        // Update DAC value
    }


}