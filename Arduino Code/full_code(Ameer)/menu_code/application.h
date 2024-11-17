#ifndef APPLICATION_H
#define APPLICATION_H

/*  Inculdes  */
#include <avr/pgmspace.h>
#include "Osci.h"
#include "bitmaps.h"
#include "eerom_map.h"

//#include <stdint.h>

// Definitions
typedef unsigned char   uint8_t;
#define BUTTON_UP_PIN           (6)
#define BUTTON_SELECT_PIN       (3)
#define BUTTON_DOWN_PIN         (5)

#define MAX_ITEM_LENGTH     (10)

// Define constants for text size and color
#define TEXT_SIZE 1
#define TEXT_COLOR WHITE

/*  Definitions */
#define MENU_ITEMS_TYPE       (1)
#define SIG_MENU_ITEMS_TYPE   (2)

//  Flags type
typedef struct flag_type
{
  uint8_t button_up_f: 1;
  uint8_t button_down_f: 1;
  uint8_t button_select_f: 1;
};

// Custom Data Types
typedef enum menus
{
  MainMenu,
  VoltmeterMenu,
  AmmeterMenu,
  OhmmeterMenu,
  SigGenMenu,
  Scope,
  ConfigMenu
};


const char menu_items [6] [MAX_ITEM_LENGTH] PROGMEM  = {
  {"Voltmeter"},
  {"Ammeter"},
  {"Ohmmeter"},
  {"Sig Gen"},
  {"Scope"},
  {"Config"}
};

// Your menu items stored in PROGMEM
const char sig_menu_items[4] [MAX_ITEM_LENGTH] PROGMEM = {
    {"Off"},
    {"Square"},
    {"Triangular"},
    {"Sine Wave"}
};


/*
typedef enum sig_type
{
  Off,
  Square,
  Triangular,
  Sine
};
*/

/*  prototypes    */
void getSignalMenuItem(uint8_t index, char *buffer, size_t bufferSize);
void getMenuItem(uint8_t index, char *buffer, size_t bufferSize);
void drawMenuItem(int y_position, uint8_t index, uint8_t type);
void configMenu(void);

#endif /* APPLICATION_H*/