/**
 * @file sin_tables.h
 * @author D. Funke
 * @brief Look up tables for sine waves of 4, 8, 12, and 16 Hz sampled at 250 Hz
 * @date 2022-11-26
 * 
 */

#ifndef SIN_TABLES_H_
#define SIN_TABLES_H_

/**
 * @brief Function to retrieve a sine value of a given frequency at a given index
 * 
 * @param frequency Waveform frequency
 * @param index Sample number
 * @return float Value corresponding to sin(2 * pi * frequency * (index * 4) / 1000)
 */
float sin_tables_get_value(int frequency, int index);

#endif /* SIN_TABLES_H_ */