// Copyright (c) 2024 Husarnet sp. z o.o.
// Authors: listed in project_root/README.md
// License: specified in project_root/LICENSE.txt

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_check.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"

#include "husarnet.h"

static const char *TAG = "main";

void app_main(void) {    
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    wifi_init();
    // In order to reduce ping, power saving mode is disabled
    esp_wifi_set_ps(WIFI_PS_NONE);

    ESP_LOGI(TAG, "Starting Husarnet client...");

    HusarnetClient* client = husarnet_init();

    // This function joins the network and blocks until the connection is established
    // Use join code obtained from the Husarnet Dashboard
    husarnet_join(client, "husarnet-esp32", "fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/XXXXXXXXXXXXXXXXXXXXXX");

    while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
