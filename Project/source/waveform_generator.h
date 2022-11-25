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
 * @brief Initializes all component waveform amplitudes to zero
 * 
 */
void waveform_generator_init(void);

/**
 * @brief Increment the amplitude value of the selected component waveform
 * 
 * @param waveform_index Integer index of component waveform to increment
 */
void waveform_generator_increment_amplitude(int waveform_index);

/**
 * @brief Decrement the amplitude value of the selected component waveform
 * 
 * @param waveform_index Integer index of component waveform to decrement
 */
void waveform_generator_decrement_amplitude(int waveform_index);

/**
 * @brief Get the amplitude of the component waveform
 * 
 * @param waveform_index Integer index of the component waveform to get amplitude
 * @return int           Unsigned integer representing component waveform amplitude
 *                       Value ranges from 0 to 9
 */
int waveform_generator_get_amplitude(int waveform_index);

/**
 * @brief Updates the current value of the output waveform every 3ms
 * 
 */
void waveform_generator_update(void);

#endif /* WAVEFORM_GENERATOR_H_ */
