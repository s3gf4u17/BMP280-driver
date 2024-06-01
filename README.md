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
    - [Code implementation](#code-implementation)
    - [Listen for incoming data](#listen-for-incoming-data)
    - [Results](#results)

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

Optionally install useful tools:

```bash
sudo apt install gnuplot minicom
```

#### Code implementation

Download driver (`bmp280_driver.c`) from the repository. In the same folder create an example file `main.c`:

```C
#include <stdio.h>
#include "pico/stdlib.h"
#include "bmp280_driver.c"

int main() {
    stdio_init_all();
    bmp280_setup();
    bmp280_read_calibration_data();
    bmp280_write_ctrl_meas();
    while (true) {
        int32_t temp = bmp280_read_temp();
        printf("%.2f\n",temp/100.0);
        sleep_ms(50);
    }
}
```

Create `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(example)
pico_sdk_init()
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(example)
```

And compile with command:

```bash
cmake -S . -B build/ =DPICO_SDK_PATH=~/pico-sdk/ && cd build && make -j8
```

As one of the results, an `example.uf2` file will appear in `build` folder. Hold down the BOOTSEL button while plugging the Pico into USB. Drag and drop `example.uf2` file onto the board. It will automatically reset and start executing code.

#### Listen for incoming data

One very powerful tool for this is `minicom`. Simply install it and run with example command:

```bash
sudo minicom -b 115200 -D /dev/ttyACM0
```

or with an additional flag if you need a datadrop:

```bash
sudo minicom -b 115200 -D /dev/ttyACM0 -C datadrop.dat
```

#### Results