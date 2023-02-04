#include "rencoder.h"
#include "pico/stdlib.h"

const int PIN_A = 0;
const int PIN_B = 1;

// Rotary encoder current and previous state variables
uint enc_a_curr;
uint enc_a_prev;
uint enc_b_curr;
uint enc_b_prev;

// Turn counter
double counter = 0.0;
double counter_prev = 0.0;

double get_counter() {
    return counter;
}

double get_counter_prev() {
    return counter_prev;
}

void set_counter_prev(double count) {
    counter_prev = count;
}

void rotation_handler() {
      // Due to encoder having an extra pulse between detents, I increment/decrement the counter by 0.5,
  // This gives a whole number output per detent. The counter can be cast to an int in the main loop.
  enc_a_curr = gpio_get(PIN_A);
  enc_b_curr = gpio_get(PIN_B);
  if ((enc_a_curr == enc_a_prev) && (enc_b_curr == enc_b_prev)) {
    // Probably "bounce"
    return;
  } else if (enc_a_curr != enc_b_prev) {
    // CW turn
    counter += 0.5;
  } else if (enc_a_curr == enc_b_prev) {
    // CCW turn
    counter -= 0.5;
  }
  enc_a_prev = enc_a_curr;
  enc_b_prev = enc_b_curr;
}

void encoder_init() {
  // initialise, set direction and setup IRQ of rotary encoder pins
  gpio_init(PIN_A);
  gpio_set_dir(PIN_A, GPIO_IN);
  gpio_set_irq_enabled_with_callback(PIN_A, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, rotation_handler);
  gpio_init(PIN_B);
  gpio_set_dir(PIN_B, GPIO_IN);
  gpio_set_irq_enabled(PIN_B, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
  enc_a_prev = gpio_get(PIN_A);
  enc_b_prev = gpio_get(PIN_B);
}