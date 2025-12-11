/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"

/* The examples use WiFi configuration that you can set via project
   configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/

static const char *TAG = "wifi softAP";


static wifi_config_t create_ap_config() {
  wifi_config_t cfg = {};

  auto &a = cfg.ap;

  constexpr size_t S = sizeof(CONFIG_ESP_WIFI_AP_SSID) - 1;
  static_assert(S <= sizeof(a.ssid));
  memcpy(a.ssid, CONFIG_ESP_WIFI_AP_SSID, S);
  a.ssid_len = S;

  constexpr size_t P = sizeof(CONFIG_ESP_WIFI_AP_PASS) - 1;
  static_assert(P <= sizeof(a.password));
  memcpy(a.password, CONFIG_ESP_WIFI_AP_PASS, P);

  a.authmode = WIFI_AUTH_WPA_WPA2_PSK;
  a.max_connection = CONFIG_ESP_WIFI_AP_MAX_CONN;

  return cfg;
}


static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_id == WIFI_EVENT_AP_STACONNECTED) {
    wifi_event_ap_staconnected_t *event =
        (wifi_event_ap_staconnected_t *)event_data;
    printf("Connect %d MAC: %s", event->aid, event->mac);
  } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
    wifi_event_ap_stadisconnected_t *event =
        (wifi_event_ap_stadisconnected_t *)event_data;
    printf("Disconnect %d MAC: %s", event->aid, event->mac);
  }
}

static inline void abort_on_error(esp_err_t err) {
  if (err != ESP_OK) {
    printf("Error in: %s", esp_err_to_name(err));
    abort();
  }
}

static void wifi_init_softap() {
  tcpip_adapter_init();

  abort_on_error(esp_event_loop_create_default());

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  abort_on_error(esp_wifi_init(&cfg));


  abort_on_error(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                            &wifi_event_handler, NULL));

  wifi_config_t wifi_config = create_ap_config();


  if (strlen(CONFIG_ESP_WIFI_AP_PASS) == 0) {
    wifi_config.ap.authmode = WIFI_AUTH_OPEN;
  }

  abort_on_error(esp_wifi_set_mode(WIFI_MODE_AP));
  abort_on_error(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
  abort_on_error(esp_wifi_start());

  ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s",
           CONFIG_ESP_WIFI_AP_SSID, CONFIG_ESP_WIFI_AP_PASS);
}

void wifi_init() {
  abort_on_error(nvs_flash_init());

  ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
  wifi_init_softap();
}