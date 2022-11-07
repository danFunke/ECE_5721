#ifndef INPUT_BUTTONS_H_
#define INPUT_BUTTONS_H_

#include <stdint.h>

enum input_buttons {
    INPUT_BUTTON_0,
    INPUT_BUTTON_1,
    INPUT_BUTTON_2,
    INPUT_BUTTON_3,
    NUM_INPUT_BUTTONS
};

void input_buttons_init(void);

uint8_t input_buttons_get_state(void);

void input_buttons_set_state(int button_index);

#endif /* INPUT_BUTTONS_H_ */
