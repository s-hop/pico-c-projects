#ifndef RENCODER_H
#define RENCODER_H

extern const int PIN_A;
extern const int PIN_B;

double get_counter();
double get_counter_prev();
void set_counter_prev(double count);
void encoder_init();

#endif // RENCODER_H