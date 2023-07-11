#include "display_graphics.hpp"
#include <cmath>

ST7789Display::ST7789Display(int8_t cs, int8_t dc, int8_t rst, int8_t rotation)
    : tft(cs,dc,rst),
    rotation(rotation)
    {}

void ST7789Display::init(){
    tft.init(240,240, SPI_MODE3);
    tft.setRotation(rotation);
    tft.setAddrWindow(0,0,239,239);
}

void ST7789Display::drawText(const int16_t & x, const int16_t & y, const char* text, const uint16_t & color, const uint8_t & size, const bool & wrap, const GFXfont* font) {
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setFont(font);
    tft.setTextWrap(wrap);
    tft.print(text);
}

void ST7789Display::drawNumber(const int16_t & x, const int16_t & y, const float & value, const uint8_t & cover_value, const uint16_t & color, const uint16_t & back_color, const uint8_t & size, const bool & wrap) {
    tft.setFont();
    tft.setCursor(x, y);
    tft.setTextColor(color,back_color);
    tft.setTextSize(size);
    tft.setTextWrap(wrap);
    tft.print((round(value)),cover_value);
}

void ST7789Display::drawNumber(const int16_t & x, const int16_t & y, const uint16_t & value, const uint8_t & cover_value, const uint16_t & color, const uint16_t & back_color, const uint8_t & size, const bool & wrap) {
    tft.setFont();
    tft.setCursor(x, y);
    tft.setTextColor(color,back_color);
    tft.setTextSize(size);
    tft.setTextWrap(wrap);
    tft.print(value,cover_value);
}

void ST7789Display::drawNumber(const int16_t & x, const int16_t & y, const int16_t & value, const uint8_t & cover_value, const uint16_t & color, const uint16_t & back_color, const uint8_t & size, const bool & wrap) {
    tft.setFont();
    tft.setCursor(x, y);
    tft.setTextColor(color,back_color);
    tft.setTextSize(size);
    tft.setTextWrap(wrap);
    tft.print(value,cover_value);
}

void ST7789Display::drawNumber(const int16_t & x, const int16_t & y, const int & value, const uint8_t & cover_value, const uint16_t & color, const uint16_t & back_color, const uint8_t & size, const bool & wrap) {
    tft.setFont();
    tft.setCursor(x, y);
    tft.setTextColor(color,back_color);
    tft.setTextSize(size);
    tft.setTextWrap(wrap);
    tft.print(value,cover_value);
}


void ST7789Display::fillScreen(const uint16_t & color){
    tft.fillScreen(color);
}

void ST7789Display::setAddrWindow(const uint16_t & x, const uint16_t & y, const uint16_t & w, const uint16_t & h){
    tft.setAddrWindow(x,y,w,h);
}

void ST7789Display::drawRect(const int16_t & x, const int16_t & y, const int16_t & w, const int16_t & h, const uint16_t & color){
    tft.drawRect(x,y,w,h,color);
}

void ST7789Display::fillRect(const int16_t & x, const int16_t & y, const int16_t & w, const int16_t & h, const uint16_t & color){
    tft.fillRect(x,y,w,h,color);    
}

void ST7789Display::drawCircle(const uint16_t & x, const uint16_t & y, const uint16_t & r, uint16_t color){
    tft.drawCircle(x,y,r,color);
}

void ST7789Display::initDebugWindow(const int16_t & position_rectangle_x, const int16_t & position_rectangle_y, const int16_t & width, const int16_t & height, const uint16_t & color, const uint16_t & bg_color){
    tft.drawRect(position_rectangle_x,position_rectangle_y,width,height,color);
}

void ST7789Display::updateDebugWindow(const int16_t & position_rectangle_x, const int16_t & position_rectangle_y, const float & controller_position_x, const float & controller_position_y, const uint16_t & radius, const uint16_t & color, const uint16_t & bg_color){
    tft.fillCircle((previous_controller_position_x+position_rectangle_x),(previous_controller_position_y+position_rectangle_y),radius+1,bg_color);
    tft.drawCircle((controller_position_x+position_rectangle_x),(controller_position_y+position_rectangle_y),radius,color);
    previous_controller_position_x = controller_position_x;
    previous_controller_position_y = controller_position_y;
}