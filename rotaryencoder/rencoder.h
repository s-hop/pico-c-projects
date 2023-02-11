#ifndef RENCODER_H
#define RENCODER_H

double get_counter();
double get_counter_prev();
void set_counter_prev(double count);
void encoder_init(uint pin_a, uint pin_b);

#endif // RENCODER_H