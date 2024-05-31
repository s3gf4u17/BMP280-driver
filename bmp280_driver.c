#ifndef bmp280_driver_c
#define bmp280_driver_c

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

#define bmp280_port_spi spi1
#define bmp280_pin_sclk 10
#define bmp280_pin_mosi 11
#define bmp280_pin_miso 12
#define bmp280_pin_cs 13

void bmp280_setup() {
    spi_init(bmp280_port_spi,1000000);
    spi_set_format(bmp280_port_spi,8,SPI_CPOL_0,SPI_CPHA_0,SPI_MSB_FIRST);
    gpio_set_function(bmp280_pin_sclk,GPIO_FUNC_SPI);
    gpio_set_function(bmp280_pin_mosi,GPIO_FUNC_SPI);
    gpio_set_function(bmp280_pin_miso,GPIO_FUNC_SPI);
    gpio_init(bmp280_pin_cs);
    gpio_set_dir(bmp280_pin_cs,GPIO_OUT);
    gpio_put(bmp280_pin_cs,1);
}

#endif