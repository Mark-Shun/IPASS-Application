# IPASS Application
This repository features an implemented application that makes use of the MPU6050 library.
https://github.com/Mark-Shun/IPASS-MPU6050

## Functionality
As of the time of writing, the application works as follows. It retrieves the calculated sensor data from the MPU6050 module, displays the values and maps them to specified coordinates. Using this functionality the position of a circle inside a box is controlled by tilting the module.

## Framework
The code is written using the platformIO framework, and it implements code specifically for my hardware setup. As such it would need quite a bit of tinkering to be able to use it for different setups.

## Third-party libraries
The following libraries have been used for this application.
- Arduino library
- Wire library
- MPU6050
- SPI
- Adafruit_ST7789
- Adafruit_GFX
- REDMP3
- SoftwareSerial