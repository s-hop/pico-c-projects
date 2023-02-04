#include "rencoder.h"
#include "pico/stdlib.h"

// GPIO pin location values on the Pico (Modify to suit).
const int PIN_A = 0;
const int PIN_B = 1;

// Current and previous state of the encoder outputs.
uint enc_a_curr;
uint enc_a_prev;
uint enc_b_curr;
uint enc_b_prev;

// Turn counter. I want integer output values per detent on the decoder, but the KY-040 I have outputs two pulses per detent.
// I use a double here so I can later increment the counter by 0.5 each pulse, giving a whole number output on each detent. (Modify to suit)
double counter = 0.0;
double counter_prev = 0.0;

double get_counter()
{
  return counter;
}

double get_counter_prev()
{
  return counter_prev;
}

void set_counter_prev(double count)
{
  counter_prev = count;
}

void rotation_handler()
{
  // If the encoder rotates in the wrong direction, switch pins on the Pico.
  enc_a_curr = gpio_get(PIN_A);
  enc_b_curr = gpio_get(PIN_B);
  if ((enc_a_curr == enc_a_prev) && (enc_b_curr == enc_b_prev))
  {
    // Probably "bounce." Ignore.
    return;
  }
  else if (enc_a_curr != enc_b_prev)
  {
    // CW turn.
    counter += 0.5;
  }
  else if (enc_a_curr == enc_b_prev)
  {
    // CCW turn.
    counter -= 0.5;
  }
  enc_a_prev = enc_a_curr;
  enc_b_prev = enc_b_curr;
}

void encoder_init()
{
  // initialise, set direction and setup IRQ of rotary encoder pins.
  gpio_init(PIN_A);
  gpio_set_dir(PIN_A, GPIO_IN);
  gpio_set_irq_enabled_with_callback(PIN_A, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, rotation_handler);
  gpio_init(PIN_B);
  gpio_set_dir(PIN_B, GPIO_IN);
  gpio_set_irq_enabled(PIN_B, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
  // Assign an initial value to the previous state variables.
  enc_a_prev = gpio_get(PIN_A);
  enc_b_prev = gpio_get(PIN_B);
}