set(Sd "../components/Sd")
set(Wifi "../components/Wifi")
set(Http "../components/Http")
set(Spi "../components/Spi")

idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS "." "${Wifi}" 
                    "${Sd}" "${Http}""${Spi}")