idf_component_register(SRCS "husarnet-web-server.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_husarnet esp_wifi esp_http_server)
