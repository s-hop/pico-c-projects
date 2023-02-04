#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "rencoder.h"

int main() {
  // Initialise USB for reading print output
  stdio_init_all();

  encoder_init();

  for (;;) {
    sleep_ms(1);
    if ((fmod(get_counter(), 1.0) == 0.0) && (get_counter() != get_counter_prev())) {
      // Only prints if encoder has turned a whole click (remainder = 0).
      printf("%d \n", (int) get_counter());
      set_counter_prev(get_counter());
    }
  }
  return 0;
}