#ifndef RENCODER_H
#define RENCODER_H

extern const int PIN_A;
extern const int PIN_B;

extern double get_counter();
extern double get_counter_prev();
extern void set_counter_prev(double count);

extern void rotation_handler();
extern void encoder_init();

#endif // RENCODER_H