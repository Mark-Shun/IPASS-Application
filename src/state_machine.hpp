#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "display_graphics.hpp"
#include "controller.hpp"
#include "defines.hpp"
#include "memory_debug.hpp"

class StateMachine{
private:
ST7789Display myDisplay;
mpu6050 mySensor;
controller myController;

byte status;

State current_state;
State previous_state;

bool flag_display_init = false;

unsigned long timer;

unsigned long previous_time;
unsigned long current_time;

char rotation_x_text[10];
char rotation_y_text[10];
char og_rotation_x_text[100];
char og_rotation_y_text[100];

float new_rotation_x = 0.0;
float new_rotation_y = 0.0;
float new_rotation_z = 0.0;
char new_rot_x_txt[10];
char new_rot_y_txt[10];
char new_rot_z_txt[10];

String string;

public:
    StateMachine(ST7789Display & myDisplay, mpu6050 & mySensor, controller & myController, byte & status);
    void setFlagDisplayInit(const bool & input);
    void setCurrentStat(State input);
    void setPrevStat(State input);
    State getCurrentStat();
    State getPrevStat();

    byte communicationFail();
    byte updateDebug();
    byte updateDebugSerial();

    int calculateFrameRate();

};

#endif