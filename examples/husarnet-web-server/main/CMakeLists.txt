idf_component_register(SRCS "husarnet-web-server.c"
                    INCLUDE_DIRS "."
                    REQUIRES husarnet_core esp_wifi esp_http_server)
