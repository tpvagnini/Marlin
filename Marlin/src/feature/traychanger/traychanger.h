/*
    Traychanger library for communication with traychanger breakout board
    Created 8/4/19 by Thomas Vagnini
 */
#pragma once
#include "../../inc/MarlinConfig.h"

class Traychanger {
public:
  Traychanger();

  void init();
  boolean loadPlate();
  boolean unloadPlate();
  void bumpPlate();
  void debug();
  static void check_version();

/* 
 *  Shelving calculations
 *  There are 8 shelves, top is 1, bottom is 8
 *  conversion methods will use the following values to calibrate
 */

#define LOAD_HEIGHT
#define BUMP_DIST           10.0    //filler value (mm)
#define SHELF_NUM           7.0
#define TOP_SHELF_Z         85.0    //mm
#define BOTTOM_SHELF_Z      253.0   //mm
#define TOP_SHELF_ULTRA     206.0     //mm
#define BOTTOM_SHELF_ULTRA  38.0      //mm
#define SHELF_DIST ((BOTTOM_SHELF_Z - TOP_SHELF_Z) / (SHELF_NUM - 1))

/* 
Shelf Measured  Linear Interp.
0	    268	
1	    202	      202
2	    178	      175
3	    151	      147
4	    123	      120
5	    92	      93
6	    65	      65
7	    38	      38
*/

  int getOccupiedShelf();
  float shelfToZ(int targetShelf);
  int heightToShelf();
  
  
  /* static void reset();
  static void mmu_loop();
  static void tool_change(uint8_t index);
  static void tool_change(const char* special);
  static uint8_t get_current_tool();
  static void set_filament_type(uint8_t index, uint8_t type);
    */

  //#if HAS_LCD_MENU && ENABLED(MMU2_MENUS)
    /*static bool unload();
    static void load_filament(uint8_t);
    static void load_all();
    static bool load_filament_to_nozzle(uint8_t index);
    static bool eject_filament(uint8_t index, bool recover);*/
  //#endif

private:
  /*static bool rx_str_P(const char* str);
  static void tx_str_P(const char* str);
  static void tx_printf_P(const char* format, int argument);
  static void tx_printf_P(const char* format, int argument1, int argument2);
  static void clear_rx_buffer();

  static bool rx_ok();
  static bool rx_start();
  

  static void command(const uint8_t cmd);
  static bool get_response(void);
  static void manage_response(const bool move_axes, const bool turn_off_nozzle);

  #if HAS_LCD_MENU && ENABLED(MMU2_MENUS)
    static void load_to_nozzle();
    static void filament_ramming();
    static void execute_extruder_sequence(const E_Step * sequence, int steps);
  #endif

  static void filament_runout();

  static bool enabled, ready, mmu_print_saved;
  static uint8_t cmd, cmd_arg, last_cmd, extruder;
  static int8_t state;
  static volatile int8_t finda;
  static volatile bool finda_runout_valid;
  static int16_t version, buildnr;
  static millis_t last_request, next_P0_request;
  static char rx_buffer[16], tx_buffer[16];

  static inline void set_runout_valid(const bool valid) {
    finda_runout_valid = valid;
    #if HAS_FILAMENT_SENSOR
      if (valid) runout.reset();
    #endif
  }*/

};

extern Traychanger traychanger;