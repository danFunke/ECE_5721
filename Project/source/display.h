/**
 * @file display.h
 * @author D. Funke
 * @brief Basic display driver for FRDM-KL25Z board using GPIO peripheral
 * @date 2022-11-16
 * 
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Enum to define the seven segment display available in the system
 * 
 */
enum seven_segment_displays {
	SEVEN_SEGMENT_DISPLAY_0,
    SEVEN_SEGMENT_DISPLAY_1,
    SEVEN_SEGMENT_DISPLAY_2,
	NUM_SEVEN_SEGMENT_DISPLAYS
};

/**
 * @brief Initializes GPIO peripheral devices needed to drive 7 segment displays
 * 
 */
void display_init(void);

/**
 * @brief 
 * 
 * @param seven_segment_index 
 * @param bitmap 
 */
void display_write_seven_segment(size_t seven_segment_display_index, uint8_t encoded_bitmap);

void display_update(void);

#endif /* DISPLAY_H_ */
