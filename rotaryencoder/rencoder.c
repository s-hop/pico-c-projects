#include "rencoder.h"
#include "pico/stdlib.h"

uint pin_a;
uint pin_b;

// Current and previous state of the encoder outputs for rotation handling.
uint enc_a_curr;
uint enc_a_prev;
uint enc_b_curr;
uint enc_b_prev;

void encoder_init(uint pin_a, uint pin_b)
{
  set_pins(pin_a, pin_b);

  // initialise, set direction and setup IRQ of rotary encoder pins.
  gpio_init(pin_a);
  gpio_set_dir(pin_a, GPIO_IN);
  gpio_set_irq_enabled_with_callback(pin_a, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, rotation_handler);
  gpio_init(pin_b);
  gpio_set_dir(pin_b, GPIO_IN);
  gpio_set_irq_enabled(pin_b, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
  // Assign an initial value to the previous state variables.
  enc_a_prev = gpio_get(pin_a);
  enc_b_prev = gpio_get(pin_b);
}

void set_pins(uint a_num, uint b_num) {
  pin_a = a_num;
  pin_b = b_num;
}


// Turn counter. I want integer output values per detent on the decoder, but the KY-040 I have outputs two pulses per detent.
// I use a double here so I can later increment the counter by 0.5 each pulse, giving a whole number output on each detent. (Modify to suit)
double counter = 0.0;
double counter_prev = 0.0;

void rotation_handler()
{
  // If the encoder rotates in the wrong direction, switch pins on the Pico.
  enc_a_curr = gpio_get(pin_a);
  enc_b_curr = gpio_get(pin_b);
  if ((enc_a_curr == enc_a_prev) && (enc_b_curr == enc_b_prev))
  {
    // Probably "bounce." Ignore.
    return;
  }
  else if (enc_a_curr != enc_b_prev)
  {
    // CW turn (increment).
    counter += 0.5;
  }
  else if (enc_a_curr == enc_b_prev)
  {
    // CCW turn (decrement).
    counter -= 0.5;
  }
  enc_a_prev = enc_a_curr;
  enc_b_prev = enc_b_curr;
}

// Counter accessor/mutator methods for monitoring rotation state in the main loop.
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