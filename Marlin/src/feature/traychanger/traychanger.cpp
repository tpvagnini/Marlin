#include "traychanger.h"
#include "../../Marlin.h"
#include "../../../module/motion.h"

Traychanger traychanger;

#define CMD_LOAD_PLATE          0x0A
#define CMD_GET_SHELF_HEIGHT    0x0B
#define CMD_UNLOAD_PLATE        0x0C
#define CMD_BUMP_PLATE          0x0D



Traychanger::Traychanger(){
    init();
}

int waitForTCBResponse(char cmd){
    long unsigned int startTime = millis();
    byte newByte = 0;
    short serialCase = 0;
    TRAYCHANGER_SERIAL.write(cmd);     //request the breakout board to start the bump sequence
    SERIAL_ECHO(cmd);
    SERIAL_ECHOLN(" written to TCB");
    while(true){
        idle();
        if(TRAYCHANGER_SERIAL.available() > 0 && serialCase != 3){
            newByte = TRAYCHANGER_SERIAL.read();
        }
        switch(serialCase){
            case 0:
                if(newByte == cmd){
                    serialCase = 1;
                    SERIAL_ECHOLN("Confirmation Recieved");   //F9 shown on LCD
                    startTime = millis();
                }
                if((millis() - startTime) > 8000){
                    SERIAL_ECHOLN("ERROR TIMEOUT on cmd confirmation");
                    return 9999;
                }
                break;
            case 1:
                if(newByte == 0xA1){     //incoming boolean
                    serialCase = 2;
                    SERIAL_ECHOLN("Expecting Boolean");
                }
                if(newByte == 0xA2){     //incoming integer
                    serialCase = 3;
                    SERIAL_ECHOLN("Expecting Int");
                }
                if((millis() - startTime) > 30000){
                    SERIAL_ECHOLN("ERROR TIMEOUT on return code");
                    return 9999;
                }
                break;
            case 2:
                if(newByte == 0x00 || newByte == 0x01){
                    SERIAL_ECHOLN("Recieved Boolean");
                    return newByte;
                }
                break;
            case 3:     //broken snce we alread got the 1st byte
                byte intPartA;
                byte intPartB;
                if(TRAYCHANGER_SERIAL.available() > 1){
                    SERIAL_ECHOLN("Recieved Integer");
                    intPartA = TRAYCHANGER_SERIAL.read();
                    intPartB = TRAYCHANGER_SERIAL.read();
                    int outputInt = (intPartA << 8) + intPartB;
                    return outputInt;
                }
                if((millis() - startTime) > 30000){
                    SERIAL_ECHOLN("ERROR TIMEOUT on recieve Int");
                    return 9999;
                }
                break;
        }
    }
}

void Traychanger::init(){
    TRAYCHANGER_SERIAL.begin(115200);
    TRAYCHANGER_SERIAL.write(0xFF);
    /*for(int i = 0; i<256; i++){
        //TRAYCHANGER_SERIAL.write(i);
        delay(100);
    }*/
    check_version();
}

boolean Traychanger::loadPlate(){
    //TRAYCHANGER_SERIAL.write(CMD_LOAD_PLATE);
    //waitForTCBResponse();
    return true;
}

boolean Traychanger::unloadPlate(){
    //add serial request
    while(true){    //add the serial responses here
        idle();
    }
    return true;
}

void Traychanger::bumpPlate(){
    waitForTCBResponse(0x0C);
    SERIAL_ECHOLN("Exiting cmd 0x0C");
}

void Traychanger::debug(){
    //will be a full report printout of values similar to TMC debug command
}

void Traychanger::check_version(){
}


int Traychanger::getOccupiedShelf(){
    float ultraHeight = (float)waitForTCBResponse(0x0D);  //filler for serial.read()
    SERIAL_ECHO("Ultraheight = ");
    SERIAL_ECHOLN(ultraHeight);
    SERIAL_ECHOLN((ultraHeight - BOTTOM_SHELF_ULTRA)/SHELF_DIST);
    return (SHELF_NUM - roundf((ultraHeight - BOTTOM_SHELF_ULTRA)/SHELF_DIST));   //calculate shelf here based on NUM_SHELVES, TOP_SHELF_ULTRA, AND BOTTOM_SHELF_ULTRA
}

float Traychanger::shelfToZ(int targetShelf){
    if(targetShelf <= SHELF_NUM)
        return (SHELF_DIST * (targetShelf-1)) + TOP_SHELF_Z;   //make sure the float math works since you're dividing and multiplying by ints
    else
        return 0.0;
}

int Traychanger::heightToShelf(){
    int shelves = ((current_position[2]+3)/SHELF_DIST) + 1;
    return shelves;
}


/*
 * SKR 1.3 will send a singal byte to request the breakout board to run a function or return a value
 * THIS IS NOT A LIBRARY, THERE'S NO CLASS, IT'S JUST HERE TO ORGANIZE CODE
 * 
 * //TODO make this an enumeration
 * 
 * List of Serial Commands
 * RECIEVED:                                  
 * run coreLoadPlate:                     0x0A
 * run coreGetShelfHeight:                0x0B
 * run coreUnloadPlate:                   0x0C
 * run coreBumpPlate:                     0x0D
 * 
 * return state of intakeLimit            0x60
 * return state of loaderLimitPlate       0x50
 * return state of loaderLimitAxis        0x52
 * return state of storageLimit           0x70    //not used yet
 * return value of intakeReflection       0x62
 * return value of intakeCurrent          0x64
 * return temperature of infraredTemp     0x66
 * return distance of storageUltrasonic   0x72
 * 
 * set intakeMotorSpeed                   0x13
 * return intakeMotorSpeed                0x23
 * set intakeServoPosition                0x12
 * return intakeServoPosition             0x22
 * extend loaderStepper                   0x10
 * retract loaderStepper                  0x11
 * set storageStepperHeight               0x14    //not used yet
 * 
 * SEND:
 * Heartbeat                              0xF0
 * okay                                   0xF1    //same as above
 * value                                  //raw value in hex sa long as it's between 0 and 255
 */

