/**
 * @file seven_segment_display_encode.c
 * @author D. Funke
 * @brief A module to encode ascii characters into 7 segment led arrays
 * @date 2022-11-16
 * 
 */

#include "seven_segment_display_encode.h"

/**
 * @brief 	Converts numerical ASCII character value to hexidecimal
 * 			representation of 7 segment display bitmap
 * 
 * @param c Numerical ASCII Character value to be encoded
 * 
 * @return 	uint8_t Hexidecimal bitmap of 7 segment display LED array 
 */
static uint8_t numeral_to_bitmap(char c) {
	static uint8_t numerals[10] = {
		0x3F, /* 0 */
		0x06, /* 1 */
		0x5B, /* 2 */
		0x4F, /* 3 */
		0x66, /* 4 */
		0x6D, /* 5 */
		0x7D, /* 6 */
		0x07, /* 7 */
		0x7F, /* 8 */
		0x6F  /* 9 */
	};

	return numerals[c - '0'];
};

/**
 * @brief 	Converts lower case ASCII character value to hexidecimal
 * 			representation of 7 segment display bitmap
 * 
 * @param c Lower case ASCII Character value to be encoded
 * 
 * @return 	uint8_t Hexidecimal bitmap of 7 segment display LED array 
 */
static uint8_t lower_case_to_bitmap(char c) {
	static uint8_t lower_case_alpha[26] = {
		0x7D, /* a */
		0x1F, /* b */
		0x0D, /* c */
		0x3D, /* d */
		0x6F, /* e */
		0x47, /* f */
		0x7B, /* g */
		0x17, /* h */
		0x10, /* i */
		0x18, /* j */
		0x57, /* k */
		0x06, /* l */
		0x54, /* m */
		0x15, /* n */
		0x1D, /* o */
		0x67, /* p */
		0x73, /* q */
		0x05, /* r */
		0x5B, /* s */
		0x0F, /* t */
		0x1C, /* u */
		0x1C, /* v */
		0x2A, /* w */
		0x37, /* x */
		0x3B, /* y */
		0x5B  /* z */
	};
	
	return lower_case_alpha[c - 'a'];
};

/**
 * @brief 	Converts upper case ASCII character value to hexidecimal
 * 			representation of 7 segment display bitmap
 * 
 * @param c Upper case ASCII Character value to be encoded
 * 
 * @return 	uint8_t Hexidecimal bitmap of 7 segment display LED array 
 */
static uint8_t upper_case_to_bitmap(char c) {
	static uint8_t upper_case_alpha[26] = {
		0x77, /* A */
		0x7F, /* B */
		0x4E, /* C */
		0x7E, /* D */
		0x4F, /* E */
		0x47, /* F */
		0x5E, /* G */
		0x37, /* H */
		0x30, /* I */
		0x3C, /* J */
		0x57, /* K */
		0x0E, /* L */
		0x54, /* M */
		0x76, /* N */
		0x7E, /* O */
		0x67, /* P */
		0x6B, /* Q */
		0x46, /* R */
		0x5B, /* S */
		0x0F, /* T */
		0x3E, /* U */
		0x3E, /* V */
		0x2A, /* W */
		0x37, /* X */
		0x3B, /* Y */
		0x5B  /* Z */
	};

	return upper_case_alpha[c - 'A'];
};

// Special character bitmaps
#define HYPHEN_BIMAP (0x01)
#define DECIMAL_POINT_BITMAP (0x80)

uint8_t seven_segment_display_encode_character(char c) {
	// Initialize output value
	uint8_t ret = 0;
	
	// Parse input value and assign output
	if (c >= '0' && c <= '9') {
		ret = numeral_to_bitmap(c);
	} else if (c >= 'a' && c <= 'z') {
		ret = lower_case_to_bitmap(c);
	} else if (c >= 'A' && c <= 'Z') {
		ret = upper_case_to_bitmap(c);
	} else if (c == '-') {
		ret = HYPHEN_BIMAP;
	} else if (c == '.') {
		ret = DECIMAL_POINT_BITMAP;
	}

	return ret;
}

size_t seven_segment_display_encode_string(const char *in, uint8_t *out, size_t in_size) {
	// Initialize counter/return variable
	size_t count = 0;

	// Obtain first character of input array
	char current_char = *in;

	// Iterate through input array, encode value, assign to output array
	while (current_char && (count < in_size)) {
		
		// If this is not the first character to encode and it is a DP
		if ((count != 0) && (current_char == '.')) {
			// Check if DP is asserted on previous encoded character
			uint8_t dp_asserted = *(out - 1) & DECIMAL_POINT_BITMAP;

			// Assert DP if not asserted on previous encoded character
			if (!dp_asserted) {
				*(out - 1) |= DECIMAL_POINT_BITMAP;
				current_char = *++in;
				*out = 0;
				count--;
			}
		} else {
			// Encode current character to bitmap and assign to output array, then increment output pointer
			*out++ = seven_segment_display_encode_character(current_char);
			
			// Increment input pointer and assign the value stored at its location to current_char
			current_char = *++in;
		}

		++count;
	}

	return count;
}