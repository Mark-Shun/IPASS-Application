#ifndef DISPLAY_GRAPHICS_HPP
#define DISPLAY_GRAPHICS_HPP
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Fonts/FreeMono9pt7b.h>
#include <SPI.h>

class ST7789Display{
private:
    Adafruit_ST7789 tft;
    int8_t rotation;
    
    float previous_controller_position_x;
    float previous_controller_position_y;

public:
    ST7789Display(int8_t cs, int8_t dc, int8_t rst, int8_t rotation);
    void init();
    void drawText(const int16_t & x, const int16_t & y, const char* text, const uint16_t & color = ST77XX_WHITE, const uint8_t & size = 1, const bool & wrap = 1, const GFXfont* font = &FreeMono9pt7b);
    void drawNumber(const int16_t & x, const int16_t & y, const float & value, const uint8_t & cover_value, const uint16_t & color = ST77XX_WHITE, const uint16_t & back_color = ST77XX_BLACK, const uint8_t & size = 1, const bool & wrap = 1);
    void drawNumber(const int16_t & x, const int16_t & y, const uint16_t & value, const uint8_t & cover_value, const uint16_t & color = ST77XX_WHITE, const uint16_t & back_color = ST77XX_BLACK, const uint8_t & size = 1, const bool & wrap = 1);
    void drawNumber(const int16_t & x, const int16_t & y, const int16_t & value, const uint8_t & cover_value, const uint16_t & color = ST77XX_WHITE, const uint16_t & back_color = ST77XX_BLACK, const uint8_t & size = 1, const bool & wrap = 1);
    void drawNumber(const int16_t & x, const int16_t & y, const int & value, const uint8_t & cover_value, const uint16_t & color = ST77XX_WHITE, const uint16_t & back_color = ST77XX_BLACK, const uint8_t & size = 1, const bool & wrap = 1);
    void fillScreen(const uint16_t & color);
    void setAddrWindow(const uint16_t & x, const uint16_t & y, const uint16_t & w, const uint16_t & h);
    void drawRect(const int16_t & x, const int16_t & y, const int16_t & w, const int16_t & h, const uint16_t & color);
    void fillRect(const int16_t & x, const int16_t & y, const int16_t & w, const int16_t & h, const uint16_t & color);
    void drawCircle(const uint16_t & x, const uint16_t & y, const uint16_t & r, uint16_t color);

    void initNormalWindow(unsigned const int & border_size, const uint16_t & color);
    void initNormalFillWindow();
    void initDebugWindow(const int16_t & position_rectangle_x, const int16_t & position_rectangle_y, const int16_t & width, const int16_t & height, const uint16_t & color, const uint16_t & bg_color);
    void updateCircle(const int16_t & position_rectangle_x, const int16_t & position_rectangle_y, const float & controller_position_x, const float & controller_position_y, const uint16_t & radius, const uint16_t & color, const uint16_t & bg_color);

};

#endif