#include "U8glib.h"
#include "bitmaps.h"
#include "application.h"
#include "Multi_Metre_Sig.h"
#include <stdint.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
// U8GLIB_SSD1306_128X64 u8g(13, 11, 8, 9, 10); // SPI connection
// for SPI connection, use this wiring:
// GND > GND
// VCC > 5V
// SCL > 13
// SDA > 11
// RES > 10
// DC > 9
// CS > 8

char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {
  {"Voltmeter"},
  {"Ammeter"},
  {"Ohmmeter"},
  {"Sig Gen"},
  {"Config"}
};

char sig_menu_items [4] [MAX_ITEM_LENGTH] = {
  {"Off"},
  {"Square"},
  {"Triangular"},
  {"Sine Wave"}
};

flag_type flags = { };

//Global Variables
menus selected_menu = MainMenu;

uint8_t item_selected = 0; // which item in the menu is selected

uint8_t item_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
uint8_t item_sel_next; // next item - used in the menu screen to draw next item after the selected one

devices device_selected = Voltmeter;
ranges  range_selected = range1;
modes mode_selected = DC_MODE;

fint32_t device_reading = 0;

void setup()
{
  MM_Init();
  u8g.setColorIndex(1);  // set the color to white

  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button
}

void loop() 
{
/***********************************************************************************************/
        /*Multi-Meter Code*/
Select_Mux(device_selected, range_selected);  //Choose device

// Update Reading
switch (device_selected)
{
  case Voltmeter:
    device_reading = Read_Volt(range_selected, mode_selected);
    break;

  case Ammeter:
    device_reading = Read_Amp(range_selected, mode_selected);
    break;

  case Ohmeter:
    device_reading = Read_Ohm(range_selected);
    break;
}

/***************************************************************************************/
  //Selection Buttons

  // Up Button  ********************************************************************************
  if((digitalRead(BUTTON_UP_PIN) == LOW))
  {
    delay(30); // Rebounce Delay
    if((digitalRead(BUTTON_UP_PIN) == LOW)  && (flags.button_up_f == 0))
    {
      item_selected--;
      if(item_selected == 255)
      {
        item_selected = NUM_ITEMS - 1;
      }
      flags.button_up_f = 1;
    }
  }
  else
  {
    flags.button_up_f = 0;
  }

  // Down Button  ********************************************************************************
  if((digitalRead(BUTTON_DOWN_PIN) == LOW))
  {
    delay(30); // Rebounce Delay
    if((digitalRead(BUTTON_DOWN_PIN) == LOW)  && (flags.button_down_f == 0))
    {
      item_selected++;
      if(item_selected >= NUM_ITEMS)
      {
        item_selected = 0;
      }

      
      flags.button_down_f = 1;
    }
  }
  else
  {
    flags.button_down_f = 0;
  }

  // Selection Button ********************************************************************************
  if((digitalRead(BUTTON_SELECT_PIN) == LOW))
  {
    delay(30); // Rebounce Delay
    if((digitalRead(BUTTON_SELECT_PIN) == LOW)  && (flags.button_select_f == 0))
    {
      switch (selected_menu)
      {
        case MainMenu:
          switch (item_selected)
          {
            case 0:
              selected_menu = VoltmeterMenu;
              break;

            case 1:
              selected_menu = AmmeterMenu;
              break;

            case 2:
              selected_menu = OhmmeterMenu;
              break;

            case 3:
              selected_menu = SigGenMenu;
              break;

            case 4:
              selected_menu = ConfigMenu;
              break;
          }
        break; // End of Case MainMenu ********************************************************************************

        case VoltmeterMenu:
          selected_menu = MainMenu;
          break; // End of Case Voltmeter ********************************************************************************

        case AmmeterMenu:
          selected_menu = MainMenu;
          break;  // End of Case Ammeter ********************************************************************************

        case OhmmeterMenu:
          selected_menu = MainMenu;
          break;  // End of Case Ohmmeter ********************************************************************************

        case SigGenMenu:
          selected_menu = MainMenu;
          break;  // End of Case SigGen ********************************************************************************

        case ConfigMenu:
          break;
      }


      flags.button_select_f = 1;
    }
  }
  else
  {
    flags.button_select_f = 0;
  }
  

/********************************************************************************/
  //Update Selected Item
  item_sel_previous = item_selected - 1;
  if(item_sel_previous == 255)
  {
    item_sel_previous = NUM_ITEMS - 1;
  }

  item_sel_next = item_selected + 1;
  if(item_sel_next >= NUM_ITEMS)
  {
    item_sel_next = 0;
  }
  
/**************************************************************************************************/
                /*OLED Main Menu*/
  u8g.firstPage();
  do
  {
    switch (selected_menu)
    {
      case MainMenu:
        // Selection box and scroll bar
        u8g.drawBitmapP(0, 0, 128/8, 64, epd_bitmap_bg);

        //Menu Item 1
        u8g.setFont(u8g_font_7x14);
        u8g.drawStr(26,15, menu_items[item_sel_previous]);
        u8g.drawBitmapP(3, 2, 16/8, 16, bitmap_arr[item_sel_previous]);

        //Menu Item 2
        u8g.setFont(u8g_font_7x14B);
        u8g.drawStr(26,37, menu_items[item_selected]);
        u8g.drawBitmapP(3, 24, 16/8, 16, bitmap_arr[item_selected]);

        //Menu Item 3
        u8g.setFont(u8g_font_7x14);
        u8g.drawStr(26,59, menu_items[item_sel_next]);
      break;

      case VoltmeterMenu:
      //Voltmeter Menu code

      break;

      case AmmeterMenu:
      //Ammeter Menu code

      break;

      case OhmmeterMenu:
      //Ohmmeter Menu Code

      break;

      case SigGenMenu:
      // Selection box and scroll bar
        u8g.drawBitmapP(0, 0, 128/8, 64, epd_bitmap_bg);

        
      //Signal Generator Menu Code

      break;

      case ConfigMenu:
      //Signal Generator Menu Code

      break;
    }

  } while(u8g.nextPage());
}
