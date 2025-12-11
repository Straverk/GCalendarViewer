#include "screen.h"


// The parameters are  RST pin, {BUS number, CS pin, DC pin,
// FREQ (0 means default), CLK pin, MOSI pin}

// ESP8266: connect LCD to 3 - D2(RES); 4 - RX(CS,not!used);
// 5 - D1(DC); H_MOSI - D7(DIN/SDI); H_SCK - D5(CLK); ESP8266

// RTOS IDF: 3 - RX(RES); 4 - D2(CS,not!used); 5 - D1(DC);
// H_MOSI - D7(DIN/SDI); H_SCK - D5(CLK);
DisplayST7789_COMMONx16_SPI screen(3, {-1, -1, 5, 0, -1, -1});

// Second version, RST not on UART
// ESP8266 RTOS IDF: 4 - D2(RES); 5 - D1(DC);
// H_MOSI - D7(DIN/SDI); H_SCK - D5(CLK);
// DisplayST7789_COMMONx16_SPI display(4,{-1, -1, 5, 0,-1,-1});

// Good ESP8266 ports image:
// https://alexgyver.ru/wp-content/uploads/2025/01/wemos-1200x593.png



static void init_lcd() {
  screen.begin(240, 320);
  screen.clear();
  screen.setFixedFont(ssd1306xled_font8x16);
}

static void init_gpio() {
#ifdef DISPLAY_BRIGHT_GPIO
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = DISPLAY_BRIGHT_GPIO;
  io_conf.pull_down_en = gpio_pulldown_t::GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = gpio_pullup_t::GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);

  gpio_set_level(gpio_num_t::GPIO_NUM_2, 1);
#endif
}


void screen_init()
{
  init_lcd();
  init_gpio();
}