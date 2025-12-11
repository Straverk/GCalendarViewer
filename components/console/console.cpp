#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "console.h"

void monitor_task(void *arg) {
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