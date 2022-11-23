/**
 * @file waveform_generator.c
 * @author D. Funke
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 */

#include "waveform_generator.h"

#define MIN_AMPLITUDE   (0)
#define MAX_AMPLITUDE   (9)

static uint8_t waveform_amplitudes[NUM_WAVEFORMS];

void waveform_generator_init(void)
{
    // Initialize all amplitudes to 0
    for (int i = 0; i < NUM_WAVEFORMS; ++i) {
        waveform_amplitudes[i] = 0;
    }
}

void waveform_generator_increment_amplitude(int waveform_index)
{
    if (waveform_index < NUM_WAVEFORMS) {
        if (waveform_amplitudes[waveform_index] < MAX_AMPLITUDE) {
            waveform_amplitudes[waveform_index]++;
        }
    }
}

void waveform_generator_decrement_amplitude(int waveform_index)
{
    if (waveform_index < NUM_WAVEFORMS) {
        if (waveform_amplitudes[waveform_index] > MIN_AMPLITUDE) {
            waveform_amplitudes[waveform_index]--;
        }
    }
}

uint8_t waveform_generator_get_amplitude(int waveform_index)
{
    return waveform_amplitudes[waveform_index];
}
