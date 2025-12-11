#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "screen.h"
#include "console.h"
#include "wifi.h"


extern "C" void app_main();


void app_main() {
  // Init
  //screen_init();
  wifi_init();

  // Create tasks
  xTaskCreate(monitor_task, "Monitor", 1024, NULL, 10, NULL);

  // xTaskCreate(init_lcd, "LCD", 1224, NULL, 10, NULL);
}