/**
 * @file system_time.h
 * @author D. Funke
 * @brief Module to provide a simple system-level wall clock
 * @date 2022-11-19
 * 
 */

#ifndef SYSTEM_TIME_H_
#define SYSTEM_TIME_H_

#include <stdint.h>

/**
 * @brief Initializes system time to 0 and subscribes to system tick event
 * 
 */
void system_time_init(void);

/**
 * @brief 
 * 
 * @return uint32_t Current system time in ms
 */
uint32_t system_time_get_ms(void);

#endif /* SYSTEM_TIME_H_ */
