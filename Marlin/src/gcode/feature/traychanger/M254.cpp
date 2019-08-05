
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

void GcodeSuite::M254() {   //
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

    int printHeight = current_position[2];

    
    traychanger.loadPlate();


  /*int8_t index = parser.intval('E', -1),
         type = parser.intval('F', -1);

  if (WITHIN(index, 0, 4) && WITHIN(type, 0, 2))
    mmu2.set_filament_type(index, type);
  else
    SERIAL_ECHO_MSG("M403 - bad arguments.")*/
}

#endif