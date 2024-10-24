#include <stdint.h>

// Definitions
#define BUTTON_UP_PIN           12
#define BUTTON_SELECT_PIN       8
#define BUTTON_DOWN_PIN         4

#define NUM_ITEMS           5
#define MAX_ITEM_LENGTH     20

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
  ConfigMenu
};

typedef enum sig_type
{
  Off,
  Square,
  Triangular,
  Sine
};