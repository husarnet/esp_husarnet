// Copyright (c) 2024 Husarnet sp. z o.o.
// Authors: listed in project_root/README.md
// License: specified in project_root/LICENSE.txt

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_check.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "protocol_examples_common.h"

#include "husarnet.h"

#define HOSTNAME  "husarnet-esp32"
// Use join code obtained from the Husarnet Dashboard
#define JOIN_CODE "fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/XXXXXXXXXXXXXXXXXXXXXX"

static const char *TAG = "main";

static esp_err_t root_get_handler(httpd_req_t *req) {
    const char resp[] = "Hello, Husarnet!";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

void start_webserver() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  httpd_handle_t server = NULL;

  ESP_LOGI(TAG, "Starting server on port %d", config.server_port);
  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_uri_t root = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = root_get_handler,
        .user_ctx  = NULL
    };
    httpd_register_uri_handler(server, &root);
  }
}

void app_main(void) {    
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    // Initialize WiFi or Ethernet, depending on the menuconfig configuration.
    ESP_ERROR_CHECK(example_connect());
    // In order to reduce ping, power saving mode is disabled
    esp_wifi_set_ps(WIFI_PS_NONE);

    ESP_LOGI(TAG, "Starting Husarnet client...");

    // Initialize Husarnet client
    HusarnetClient* client = husarnet_init();

    // This function joins the network and blocks until the connection is established
    husarnet_join(client, HOSTNAME, JOIN_CODE);

    while (!husarnet_is_joined(client)) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Joining Husarnet network...");
    }

    // Get Husarnet IP address
    char ip[HUSARNET_IP_STR_LEN];
    husarnet_get_ip_address(client, ip, HUSARNET_IP_STR_LEN);
    ESP_LOGI(TAG, "Husarnet IP address: %s", ip);

    // Start the web server
    start_webserver();

    while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
