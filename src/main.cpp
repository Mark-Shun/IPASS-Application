#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "display_graphics.hpp"
#include "controller.hpp"
#include "defines.hpp"
#include "state_machine.hpp"

State execute_state;
byte status;

ST7789Display myDisplay(TFT_CS,TFT_DC,TFT_RST,ROTATION);
mpu6050 mySensor;
controller myController(mySensor);

StateMachine myStateMachine(myDisplay, mySensor, myController,status);

void stateChange(const uint8_t & input){
  if(input == green_button){
    switch(execute_state){
      case NORMAL:
        execute_state = NORMALFILL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case NORMALFILL:
        execute_state = DEBUG;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case DEBUG:
        execute_state = DEBUGSERIAL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case DEBUGSERIAL:
        execute_state = NORMAL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      default:
        break;
    }
  } else{
    switch(execute_state){
      case DEBUGSERIAL:
        execute_state = DEBUG;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case DEBUG:
        execute_state = NORMALFILL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case NORMALFILL:
        execute_state = NORMAL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      case NORMAL:
        execute_state = DEBUGSERIAL;
        myStateMachine.setFlagDisplayInit(false);
        break;
      default:
        break;
    }
  }
}

void setup(void) {
  pinMode(yellow_button, INPUT);
  pinMode(blue_button,INPUT);
  pinMode(green_button,INPUT);
  byte status;
  Serial.begin(115200);
  Wire.begin();
  myDisplay.init();
  myDisplay.fillScreen(ST77XX_BLACK);
  myDisplay.drawText(10,100,"Setting up",ST77XX_GREEN,2);
  myDisplay.drawText(0,140,"Please don't move controller",ST77XX_ORANGE);
  
  delay(100);
  status = myController.init();
  if(status != 0){
    myDisplay.fillScreen(ST77XX_BLACK);
    delay(10);
    while(status != 0){
      myDisplay.drawText(55,50,"MPU6050",ST77XX_RED,2);
      myDisplay.drawText(70,120,"INIT",ST77XX_RED,2);
      myDisplay.drawText(70,180,"FAIL",ST77XX_RED,2);
      myDisplay.drawText(50,220,"Status = ",ST77XX_RED,1);
      myDisplay.drawNumber(150,210,status,5,ST77XX_ORANGE, ST77XX_BLACK,2);
      delay(100);
      status = myController.init();
    }
  }
  execute_state = NORMAL;
}

void loop() {  
  switch (execute_state){
    case NORMAL:
      status = myStateMachine.updateNormal();
      if(status != 0){
        execute_state = COMMFAIL;
        myStateMachine.setPrevStat(NORMAL);
        myStateMachine.setFlagDisplayInit(false);
      }
      if(digitalRead(green_button) == HIGH){
        stateChange(green_button);
      }
      else if(digitalRead(blue_button) == HIGH){
        stateChange(blue_button);
      }
      break;
    case NORMALFILL:
      status = myStateMachine.updateNormal();
      if(status != 0){
        execute_state = COMMFAIL;
        myStateMachine.setPrevStat(NORMALFILL);
        myStateMachine.setFlagDisplayInit(false);
      }
      if(digitalRead(green_button) == HIGH){
        stateChange(green_button);
      }
      else if(digitalRead(blue_button) == HIGH){
        stateChange(blue_button);
      }
      break;
    case DEBUG:
      status = myStateMachine.updateDebug();
      if(status != 0){
        execute_state = COMMFAIL;
        myStateMachine.setPrevStat(DEBUG);
        myStateMachine.setFlagDisplayInit(false);
      }
      if(digitalRead(green_button) == HIGH){
        stateChange(green_button);
      }
      else if(digitalRead(blue_button) == HIGH){
        stateChange(blue_button);
      }
      break;
    case DEBUGSERIAL:
      status = myStateMachine.updateDebugSerial();
      if(status != 0){
        execute_state = COMMFAIL;
        myStateMachine.setPrevStat(DEBUGSERIAL);
        myStateMachine.setFlagDisplayInit(false);
      }
      if(digitalRead(green_button) == HIGH){
        stateChange(green_button);
      }
      else if(digitalRead(blue_button) == HIGH){
        stateChange(blue_button);
      }
      break;

    case COMMFAIL:
      status = myStateMachine.communicationFail();
      if(status == 0){
        execute_state = myStateMachine.getPrevStat();
        myStateMachine.setFlagDisplayInit(false);
      }
      break;
    default:
      break;
  }

}
