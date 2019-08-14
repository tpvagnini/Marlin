
#include "../../../inc/MarlinConfigPre.h"
#include "../../gcode.h"
#include "../../../module/motion.h"
#include "../../../feature/traychanger/traychanger.h"

/* 
 * M254 Unload Plate Sequence for Traychanger systems
*/

#if ENABLED(TRAYCHANGER)

//We need to make a startup thing to make sure that the plate is clean somehow, possibly by using the heater and temp sensor, 
//we should also have a lower z endstop so we can home the machine on startup in which case we have an unknown height model on the bed and don't know the z position
//(may want to use axis_unhomed_error(), see G01 for example)
//for mqp could implement a camera system that also detects print failures

void GcodeSuite::M254() {   //Unload plate
    /* 1. Get current z position as the print height -> calculate number of shelves, can put a helper function in the traychanger class that doesn't use serial //motion.h has current_position[XYZE] and void report_current_position();
     * 2. Get the ultrasonic distance over serial and figure out the target shelf
     * 3. Convert shelf target to z and check that it's within the machine limits
     * 4. Move to proper z height //motion.cpp has do_blocking_move_to_xy() and do_blocking_move_to_z()
     * 5. run the unload plate command on the breakout board
     * 6. Move the z table up a bit
     * 7. Run the plate bump command on the breakout board
     * 8. Home printer //motion.cpp includes homeaxis() and do_homing_move()
     * 9. Run M255?
     */

    int targetShelf = traychanger.getOccupiedShelf() + traychanger.heightToShelf();
    SERIAL_ECHO("Target Shelf: ");
    SERIAL_ECHOLN(targetShelf);
    int targetZ = traychanger.shelfToZ(targetShelf);
    SERIAL_ECHO("Target Z: ");
    SERIAL_ECHOLN(targetZ);
    if(targetZ > 0.0){
        do_blocking_move_to_z(targetZ, 10.0);
    }
    else{
        //exit and return an error / full storage message DO NOT CONTINUE PROGRAM;
    }
    //traychanger.unloadPlate();
    //do_blocking_move_to_z(current_position[2] + BUMP_DIST);
    //traychanger.bumpPlate();
    //home axis
    //M255(false);
}

void GcodeSuite::M255(boolean wait){
    //home xy and move to safe position
    //home z 
    //move z to LOAD_HEIGHT
    traychanger.bumpPlate();
    /*if(!traychanger.loadPlate()){
        //if loading fails, display the error on the lcd and over serial, exit if wait == false, wait if wait == true
    }*/
}

void GcodeSuite::M256(){

}

#endif