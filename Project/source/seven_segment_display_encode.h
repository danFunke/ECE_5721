/**
 * @file seven_segment_display_encode.h
 * @author D. Funke
 * @brief A module to encode ascii characters into 7 segment led arrays
 * @date 2022-11-16
 * 
 */

#ifndef SEVEN_SEGMENT_DISPLAY_ENCODE_H_
#define SEVEN_SEGMENT_DISPLAY_ENCODE_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Translates a single character into a bitmap representation of its respective
 *	      pattern on a seven segment display
 * 
 * @param c         ASCII Character value
 * 
 * @return uint8_t  LED bitmap
 */
uint8_t seven_segment_display_encode_character(char c);

/**
 * @brief Translates an array of characters into bitmap representations of their
 *	      respective pattern on a seven segment display
 * 
 * @param in        Pointer to character array (string) to be encoded
 * @param out       Pointer to uint8_t array of resultant bitmaps
 * @param in_size   Size of input array
 * 
 * @return size_t   Size of output array
 */
size_t seven_segment_display_encode_string(const char *in, uint8_t *out, size_t in_size);


#endif /* SEVEN_SEGMENT_DISPLAY_ENCODE_H_ */