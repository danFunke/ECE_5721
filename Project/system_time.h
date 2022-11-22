/**
 * @file system_time.h
 * @author your name (you@domain.com)
 * @brief Module to provide a simple system-level wall clock
 * @date 2022-11-19
 * 
 */

#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H_

#include <stdint.h>

/**
 * @brief 
 * 
 */
void system_time_init(void);

/**
 * @brief 
 * 
 */
uint32_t system_time_get_ms(void);

#endif /* SYSTEM_TIME_H_ */