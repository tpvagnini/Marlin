#include "traychanger.h"

Traychanger traychanger;

#define CMD_LOAD_PLATE          0x0A
#define CMD_GET_SHELF_HEIGHT    0x0B
#define CMD_UNLOAD_PLATE        0x0C
#define CMD_BUMP_PLATE          0x0D



Traychanger::Traychanger(){
}

void Traychanger::init(){
    TRAYCHANGER_SERIAL.begin(115200);
}

void Traychanger::loadPlate(){
    TRAYCHANGER_SERIAL.write(CMD_LOAD_PLATE);
}

void Traychanger::unloadPlate(){

}

void Traychanger::debug(){

}

void Traychanger::check_version(){

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

