#include "state_machine.hpp"

StateMachine::StateMachine(ST7789Display & myDisplay, mpu6050 & mySensor, controller & myController, byte & status):
    myDisplay(myDisplay),
    mySensor(mySensor),
    myController(myController),
    status(status)
{}

void StateMachine::setFlagDisplayInit(const bool & input){
    this->flag_display_init = input;
}

void StateMachine::setCurrentStat(State input){
    current_state = input;
}

void StateMachine::setPrevStat(State input){
    previous_state = input;
}

State StateMachine::getCurrentStat(){
    return current_state;
}

State StateMachine::getPrevStat(){
    return previous_state;
}

byte StateMachine::communicationFail(){
    if(flag_display_init == false){
        myDisplay.init();
        myDisplay.fillScreen(ST77XX_BLACK);
        flag_display_init = true;
    }
    myDisplay.drawText(55,50,"MPU6050",ST77XX_RED,2);
    myDisplay.drawText(70,120,"COMM",ST77XX_RED,2);
    myDisplay.drawText(70,180,"FAIL",ST77XX_RED,2);
    myDisplay.drawText(50,220,"Status = ",ST77XX_RED,1);
    myDisplay.drawNumber(150,210,status,5,ST77XX_ORANGE, ST77XX_BLACK,2);
    status = mySensor.communicationCheck();
    delay(50);
    return status;
}

byte StateMachine::updateNormal(){
    if(flag_display_init == false){
        myDisplay.init();
        myDisplay.fillScreen(ST77XX_BLACK);

        myDisplay.initNormalWindow(20,ST77XX_ORANGE);
        flag_display_init = true;
    }
    status = mySensor.communicationCheck();
    myController.update();
    myController.mapAnglesToCoordinates(210,210,30,210,30,210);

    if(digitalRead(yellow_button) == HIGH){
        myController.reset(210,210);
    }
    
    myDisplay.updateCircle(0,0,myController.getPositionX(),myController.getPositionY(),10,ST77XX_CYAN,ST77XX_BLACK);

    return status;

}

byte StateMachine::updateNormalFill(){
    if(flag_display_init == false){
        myDisplay.init();
        myDisplay.fillScreen(ST77XX_BLACK);

        myDisplay.initNormalFillWindow();
        flag_display_init = true;
    }
    status = mySensor.communicationCheck();
    myController.update();
    myController.mapAnglesToCoordinates(240,240,0,240,0,240);

    if(digitalRead(yellow_button) == HIGH){
        myController.reset(240,240);
    }
    
    myDisplay.updateCircle(0,0,myController.getPositionX(),myController.getPositionY(),10,ST77XX_CYAN,ST77XX_BLACK);

    return status; 
}

void StateMachine::updateDebugScreen(){
    myDisplay.updateCircle(80,150,myController.getPositionX(),myController.getPositionY(),4,ST77XX_RED,ST77XX_BLACK);

    if(millis()-previous_timer > 16){ // Update the value drawings every 16ms (approxiametely 60fps)
        myDisplay.drawNumber(120,10,myController.getPositionX(),10, ST77XX_CYAN,ST77XX_BLACK,2, false);
        myDisplay.drawNumber(120,30,myController.getPositionY(),10,ST77XX_CYAN,ST77XX_BLACK,2, false);

        myDisplay.drawNumber(120,50,myController.getRawGyroX(),10, ST77XX_GREEN,ST77XX_BLACK,2, false);
        myDisplay.drawNumber(120,70,myController.getRawGyroY(),10, ST77XX_GREEN,ST77XX_BLACK,2, false);

        myDisplay.drawNumber(120,90,myController.getAngleX(),10, ST77XX_ORANGE, ST77XX_BLACK,2, false);
        myDisplay.drawNumber(120,110,myController.getAngleY(),10, ST77XX_ORANGE, ST77XX_BLACK,2, false);
        myDisplay.drawNumber(120,130,myController.getAngleZ(),10, ST77XX_ORANGE, ST77XX_BLACK,2, false);
        previous_timer = millis();
    }

    myDisplay.drawNumber(42,210,calculateFrameRate(),5,ST77XX_YELLOW,ST77XX_BLACK,2,false);
}

byte StateMachine::updateDebug(){
    if(flag_display_init == false){
        previous_timer = millis();
        previous_time = millis();
        myDisplay.init();
        myDisplay.fillScreen(ST77XX_BLACK);

        myDisplay.drawText(0,15, "Position X: ");
        myDisplay.drawText(0,40,"Position Y: ");

        myDisplay.drawText(0,60,"Raw Rot X:");
        myDisplay.drawText(0,80,"Raw Rot Y:");

        myDisplay.drawText(0,100,"Angle X:");
        myDisplay.drawText(0,120,"Angle Y:");
        myDisplay.drawText(0,140,"Angle Z:");

        myDisplay.drawText(0,220,"FPS:");

        myDisplay.initDebugWindow(80,150,80,80,ST77XX_RED,ST77XX_BLACK);
        flag_display_init = true;
    }
    status = mySensor.communicationCheck();
    myController.update();
    myController.mapAnglesToCoordinates(80,80,10,70,10,70);

    if(digitalRead(yellow_button) == HIGH){
        myController.reset(80,80);
    }
    
    updateDebugScreen();

    return status;
}

byte StateMachine::updateDebugSerial(){
    if(flag_display_init == false){
        myDisplay.init();
        myDisplay.fillScreen(ST77XX_BLACK);
        myDisplay.drawText(50,120,"Serial",ST77XX_YELLOW,2);
        flag_display_init = true;
    }
    myController.update();
    myController.mapAnglesToCoordinates(240,240,0,240,0,240);

    if((millis()-timer)>50){
        Serial.print("AngleX: "); Serial.print(myController.getAngleX()); Serial.print("\tAngleY: "); Serial.print(myController.getAngleY()); Serial.print("\tAngleZ: "); Serial.println(myController.getAngleZ());
        Serial.print("Position X: "); Serial.print(myController.getPositionX()); Serial.print("\tPosition Y: "); Serial.println(myController.getPositionY());
        timer = millis();
    }
    status = mySensor.communicationCheck();
    return status;
}

int StateMachine::calculateFrameRate(){
    current_time = millis();
    unsigned long delta_time = current_time - previous_time;
    float frame_rate = 1000.0/delta_time;
    previous_time = current_time;
    return static_cast<int>(frame_rate);
}