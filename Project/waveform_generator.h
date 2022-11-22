/**
 * @file waveform_generator.h
 * @author D. Funke
 * @brief   Module to generate a complex sinusoidal waveform with high
 *          frequency noise contamination
 * 
 */

#ifndef WAVEFORM_GENERATOR_H_
#define WAVEFORM_GENERATOR_H_

/**
 * @brief 
 * 
 */
enum component_wave_names {
    DELTA_WAVE,
    THETA_WAVE,
    ALPHA_WAVE,
    BETA_WAVE,
    NUM_COMPONENT_WAVES
};

/**
 * @brief 
 * 
 */
void waveform_generator_init(void);

/**
 * @brief 
 * 
 * @param target_waveform 
 */
void waveform_generator_increment_amplitude(int target_waveform);

/**
 * @brief 
 * 
 * @param target_waveform 
 */
void waveform_generator_decrement_amplitude(int target_waveform);

/**
 * @brief 
 * 
 * @param target_waveform 
 * @return int 
 */
int waveform_generator_get_amplitude(int target_waveform);

/**
 * @brief 
 * 
 */
void waveform_generator_update(void);

#endif /* WAVEFORM_GENERATOR_H_ */