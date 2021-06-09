cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(organ  C CXX ASM)


pico_sdk_init()

add_executable(organ organ.cpp )

# create map/bin/hex file etc.
 pico_add_extra_outputs(organ)

pico_enable_stdio_usb(organ 1)
pico_enable_stdio_uart(organ 0)

 # Pull in our (to be renamed) simple get you started dependencies
 target_link_libraries(organ pico_stdlib hardware_i2c hardware_spi)


 # add url via pico_set_program_url
 #example_auto_set_url(mpu6050_i2c)
