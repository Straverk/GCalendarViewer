#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>


extern "C" void app_main();


void init_lcd() {
  
}


void init_gpio() {
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = GPIO_Pin_2;
  io_conf.pull_down_en = gpio_pulldown_t::GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = gpio_pullup_t::GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);

  gpio_set_level(gpio_num_t::GPIO_NUM_2, 1);
}

static void enable_led_task(void *arg) {
  for (;;) {
    gpio_set_level(gpio_num_t::GPIO_NUM_2, 1);
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}
static void disable_led_task(void *arg) {
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(180));
    gpio_set_level(gpio_num_t::GPIO_NUM_2, 0);
  }
}


static void monitor_task(void *arg) {
  static char buf[512];

  for (;;) {
    vTaskList(buf);

    printf("\n================ MINI TOP ================\nName\t      State "
           "Priority  FreeStack ID\n");
    printf("%s\n", buf);

    printf("Free heap: %d bytes\n", esp_get_free_heap_size());
    printf("---------------- -------- ----------------\n");

    vTaskDelay(pdMS_TO_TICKS(20000));
  }
}

void app_main() {
  // Init
  init_lcd();
  init_gpio();


  // Create tasks
  xTaskCreate(enable_led_task, "Led on", 155, NULL, 10, NULL);
  xTaskCreate(disable_led_task, "Led off", 155, NULL, 10, NULL);

  xTaskCreate(monitor_task, "Monitor", 1024, NULL, 10, NULL);
}