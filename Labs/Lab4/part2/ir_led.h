#ifndef IR_LED_H_
#define IR_LED_H_

enum ir_led_states {
    IR_LED_OFF,
    IR_LED_ON
};

void ir_led_init(void);

void ir_led_write_state(int state);

#endif /* IR_LED_H_ */