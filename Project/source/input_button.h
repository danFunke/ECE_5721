/**
 * @file input_button.h
 * @author D. Funke
 * @brief 
 * @date 2022-11-22
 * 
 */

#ifndef INPUT_BUTTON_H_
#define INPUT_BUTTON_H_

enum input_buttons {
    INC_DELTA,
    DEC_DELTA,
    INC_THETA,
    DEC_THETA,
    INC_ALPHA,
    DEC_ALPHA,
    INC_BETA,
    DEC_BETA,
    NUM_INPUT_BUTTONS
};

/**
 * @brief Initializes GPIO pots for input buttons
 * 
 */
void input_button_init(void);

/**
 * @brief Interrupt handler; Executes when an input button is pressed
 * 
 */
void PORTD_IRQHandler(void);

#endif /* INPUT_BUTTON_H_ */
