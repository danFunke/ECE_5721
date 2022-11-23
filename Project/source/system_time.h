#ifndef SYSTEM_TIME_H_
#define SYSTEM_TIME_H_

#include <stdint.h>

void system_time_init(void);

uint32_t system_time_get_ms(void);

#endif /* SYSTEM_TIME_H_ */
