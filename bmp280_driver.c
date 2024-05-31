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

typedef struct calib_data_s {
    uint16_t dig_T1;
    int16_t dig_T2,dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;
} t_calibration_data;

struct calib_data_s cd;

void bmp280_readCalibrationData() {
    uint8_t address = 0x88 | 0x80;
    uint8_t buffer[24];
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&address,1);
    spi_read_blocking(bmp280_port_spi,0,buffer,24);
    gpio_put(bmp280_pin_cs,1);
    cd.dig_T1 = buffer[0] | (buffer[1]<<8);
    cd.dig_T2 = buffer[2] | (buffer[3]<<8);
    cd.dig_T3 = buffer[4] | (buffer[5]<<8);
    cd.dig_P1 = buffer[6] | (buffer[7]<<8);
    cd.dig_P2 = buffer[8] | (buffer[9]<<8);
    cd.dig_P3 = buffer[10] | (buffer[11]<<8);
    cd.dig_P4 = buffer[12] | (buffer[13]<<8);
    cd.dig_P5 = buffer[14] | (buffer[15]<<8);
    cd.dig_P6 = buffer[16] | (buffer[17]<<8);
    cd.dig_P7 = buffer[18] | (buffer[19]<<8);
    cd.dig_P8 = buffer[20] | (buffer[21]<<8);
    cd.dig_P9 = buffer[22] | (buffer[23]<<8);
};

uint8_t bmp280_readRegisterId() {
    uint8_t address = 0xD0 | 0x80;
    uint8_t value = 0xFF;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&address,1);
    spi_read_blocking(bmp280_port_spi,0,&value,1);
    gpio_put(bmp280_pin_cs,1);
    return value;
}

void bmp280_softReset() {
    uint8_t addval[2];
    addval[0] = 0xE0 | 0x7F;
    addval[1] = 0xB6;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&addval,2);
    gpio_put(bmp280_pin_cs,1);
};

#endif