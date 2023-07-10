#ifndef DEFINES_HPP
#define DEFINES_HPP

#define TFT_CS        10 // Not used for ST7789
#define TFT_RST        9 // For ST7789 RES
#define TFT_DC         8 // For ST7789 DC
#define ROTATION       2

#define RADIAL_TO_DEGREES 57.29578
#define DEFAULT_GYRO_COEFF 0.98

enum State {
  NORMAL,
  DEBUG,
  DEBUGSERIAL,
  COMMFAIL
};

const int yellow_button = 6;

#endif