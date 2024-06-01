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
    spi_init(bmp280_port_spi,500000);
    spi_set_format(bmp280_port_spi,8,SPI_CPOL_0,SPI_CPHA_0,SPI_MSB_FIRST);
    gpio_set_function(bmp280_pin_sclk,GPIO_FUNC_SPI);
    gpio_set_function(bmp280_pin_mosi,GPIO_FUNC_SPI);
    gpio_set_function(bmp280_pin_miso,GPIO_FUNC_SPI);
    gpio_init(bmp280_pin_cs);
    gpio_set_dir(bmp280_pin_cs,GPIO_OUT);
    gpio_put(bmp280_pin_cs,1);
}

typedef struct calib_data_s {
    uint16_t dig_T1; // 28355
    int16_t dig_T2,dig_T3; // 26467,50
    uint16_t dig_P1;
    int16_t dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;
} bmp280_calib_data_t;

bmp280_calib_data_t cd;

void bmp280_read_calibration_data() {
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
}

uint8_t bmp280_read_register_id() {
    uint8_t address = 0xD0 | 0x80;
    uint8_t value = 0xFF;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&address,1);
    spi_read_blocking(bmp280_port_spi,0,&value,1);
    gpio_put(bmp280_pin_cs,1);
    return value;
}

void bmp280_soft_reset() {
    uint8_t addval[2];
    addval[0] = 0xE0 & 0x7F;
    addval[1] = 0xB6;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,addval,2);
    gpio_put(bmp280_pin_cs,1);
}

uint8_t bmp280_read_status() {
    uint8_t reg = 0xF3 | 0x80;
    uint8_t val;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&reg,1);
    spi_read_blocking(bmp280_port_spi,0,&val,1);
    gpio_put(bmp280_pin_cs,1);
    uint8_t measuring = val & 0b00001000;
    uint8_t im_update = val & 0b00000001;
    uint8_t status = measuring | im_update;
    return status;
}

void bmp280_write_ctrl_meas() {
    uint8_t addval[2];
    addval[0] = 0xF4 & 0x7F;
    addval[1] = 0x27;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&addval,2);
    gpio_put(bmp280_pin_cs,1);
}

void bmp280_write_config(uint8_t tsb, uint8_t filter, uint8_t spi3wen) {
    uint8_t addval[2];
    addval[0] = 0xF5 & 0x7F;
    addval[1] = tsb | filter | spi3wen;
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,addval,2);
    gpio_put(bmp280_pin_cs,1);
}

int32_t bmp280_read_raw_temp() {
    uint8_t reg = 0xFA | 0x80;
    uint8_t buffer[3];
    gpio_put(bmp280_pin_cs,0);
    spi_write_blocking(bmp280_port_spi,&reg,1);
    spi_read_blocking(bmp280_port_spi,0,buffer,3);
    gpio_put(bmp280_pin_cs,1);
    int32_t rawtemp = ((uint32_t) buffer[0] << 12) | ((uint32_t) buffer[1] << 4) | ((uint32_t) buffer[2] >> 4);
    return rawtemp;
}

int32_t bmp280_read_temp() {
    int32_t rawtemp = bmp280_read_raw_temp();
    int32_t var1,var2,T;
    var1 = ((((rawtemp >> 3) - ((int32_t) cd.dig_T1 << 1))) * ((int32_t) cd.dig_T2)) >> 11;
    var2 = (((((rawtemp >> 4) - ((int32_t) cd.dig_T1)) * ((rawtemp >> 4) - ((int32_t) cd.dig_T1))) >> 12) * ((int32_t) cd.dig_T3)) >> 14;
    T = ((var1+var2)*5+128)>>8;
    return T;
}

#endif