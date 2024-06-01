### Table of Contents

- [Configuring the sensor connection](#configuring-the-sensor-connection)
    - [bmp280_port_spi](#bmp280_port_spi)
    - [bmp280_pin_sclk](#bmp280_pin_sclk)
    - [bmp280_pin_mosi](#bmp280_pin_mosi)
    - [bmp280_pin_miso](#bmp280_pin_miso)
    - [bmp280_pin_cs](#bmp280_pin_cs)
- [Functions available to the user](#functions-available-to-the-user)
    - [bmp280_setup](#bmp280_setup)
    - [bmp280_read_calibration_data](#bmp280_read_calibration_data)
    - [bmp280_read_register_id](#bmp280_read_register_id)
    - [bmp280_soft_reset](#bmp280_soft_reset)
    - [bmp280_read_status](#bmp280_read_status)
    - [bmp280_write_ctrl_meas](#bmp280_write_ctrl_meas)
    - [bmp280_write_config](#bmp280_write_config)
    - [bmp280_read_raw_temp](#bmp280_read_raw_temp)
    - [bmp280_read_temp](#bmp280_read_temp)
- [Example of how to use](#example-of-how-to-use)
    - [Environment setup](#environment-setup)

<hr>

### Configuring the sensor connection

#### bmp280_port_spi

#### bmp280_pin_sclk

#### bmp280_pin_mosi

#### bmp280_pin_miso

#### bmp280_pin_cs

<hr>

### Functions available to the user

#### bmp280_setup

#### bmp280_read_calibration_data

#### bmp280_read_register_id

#### bmp280_soft_reset

#### bmp280_read_status

#### bmp280_write_ctrl_meas

#### bmp280_write_config

#### bmp280_read_raw_temp

#### bmp280_read_temp

<hr>

### Example of how to use

#### Environment setup

Before working with Pico, install all required system packages:

```bash
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

Then clone the official Pico SDK repository:

```bash
git clone -b master https://github.com/raspberrypi/pico-sdk ~/pico-sdk/
cd ~/pico-sdk/
git submodule update --init
```

Optionally install install useful tools:

```bash
sudo apt install gnuplot minicom
```