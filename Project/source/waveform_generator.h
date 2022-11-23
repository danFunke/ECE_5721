/**
 * @file waveform_generator.h
 * @author D. Funke
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 */

#ifndef WAVEFORM_GENERATOR_H_
#define WAVEFORM_GENERATOR_H_

#include <stdint.h>

enum waveforms {
    DELTA,
    THETA,
    ALPHA,
    BETA,
    NUM_WAVEFORMS
};

/**
 * @brief 
 * 
 */
void waveform_generator_init(void);

/**
 * @brief 
 * 
 * @param waveform_index 
 */
void waveform_generator_increment_amplitude(int waveform_index);

/**
 * @brief 
 * 
 * @param waveform_index 
 */
void waveform_generator_decrement_amplitude(int waveform_index);

/**
 * @brief 
 * 
 * @param waveform_index 
 * @return uint8_t 
 */
uint8_t waveform_generator_get_amplitude(int waveform_index);

#endif /* WAVEFORM_GENERATOR_H_ */
