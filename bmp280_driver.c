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

#endif