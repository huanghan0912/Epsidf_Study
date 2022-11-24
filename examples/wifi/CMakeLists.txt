set(Wifi "/core/Wifi")
idf_component_register(SRCS "wifi_main.cpp"
                    INCLUDE_DIRS "." "${Wifi}")