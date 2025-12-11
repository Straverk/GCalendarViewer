#pragma once

#include "driver/gpio.h"


// Display bright pin, not define - not use
#define DISPLAY_BRIGHT_GPIO GPIO_Pin_2

#ifdef DISPLAY_BRIGHT_GPIO
// This need to change too
const gpio_num_t gpio_bright_pin = gpio_num_t::GPIO_NUM_2;
#endif
// GPIO2 - D4
