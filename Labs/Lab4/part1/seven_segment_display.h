#ifndef SEVEN_SEGMENT_DISPLAY_H_
#define SEVEN_SEGMENT_DISPLAY_H_

#include <stdint.h>

void seven_segment_display_init(void);

void seven_segment_display_print_0(uint8_t encoded_val);

void seven_segment_display_print_1(uint8_t encoded_val);

#endif /* SEVEN_SEGMENT_DISPLAY_H_ */