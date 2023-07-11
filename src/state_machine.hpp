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

// Used for drawing
unsigned long timer;
unsigned long previous_timer;

// Used for fps
unsigned long previous_time;
unsigned long current_time;

String string;

public:
    StateMachine(ST7789Display & myDisplay, mpu6050 & mySensor, controller & myController, byte & status);
    void setFlagDisplayInit(const bool & input);
    void setCurrentStat(State input);
    void setPrevStat(State input);
    State getCurrentStat();
    State getPrevStat();

    byte communicationFail();

    byte updateNormal();
    byte updateNormalFill();
    void updateDebugScreen();
    byte updateDebug();
    byte updateDebugSerial();

    int calculateFrameRate();

};

#endif