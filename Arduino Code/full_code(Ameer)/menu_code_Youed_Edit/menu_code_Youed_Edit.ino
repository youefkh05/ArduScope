
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"
#include "bitmaps.h"
#include "application.h"
#include "Multi_Metre_Sig.h"
//#include <stdint.h>

// OLED display width and height, in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4        // Reset pin (set to -1 if sharing Arduino reset pin)

Adafruit_SH1106 oled(OLED_RESET);


// Define constants for text size and color
#define TEXT_SIZE 1
#define TEXT_COLOR WHITE

// Function to draw a menu item
void drawMenuItem(int y_position, const char* item_text, const uint8_t* item_bitmap) {
    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(26, y_position);
    oled.print(item_text);
    oled.drawBitmap(3, y_position - 13, item_bitmap, 16, 16, TEXT_COLOR); // Adjusted y position for bitmap
}

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

float device_reading = 0;

void setup()
{
  MM_Init();
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // Start the display with the appropriate I2C address
  /*
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop here if allocation fails
  }
  */
  oled.clearDisplay();
  oled.display();  // Initial display update
  // Set the text color to white
  oled.setTextColor(WHITE);

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
  /* OLED Main Menu */
  oled.clearDisplay(); // Clear the display before drawing each frame
  switch (selected_menu) {
      case MainMenu:
          // Selection box and scroll bar
          oled.drawBitmap(0, 0, epd_bitmap_bg, SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_COLOR);

          // Draw Menu Items
          drawMenuItem(15, menu_items[item_sel_previous], bitmap_arr[item_sel_previous]); // Menu Item 1
          drawMenuItem(37, menu_items[item_selected], bitmap_arr[item_selected]); // Menu Item 2
          drawMenuItem(59, menu_items[item_sel_next], bitmap_arr[item_sel_next]); // Menu Item 3
          break;

      case VoltmeterMenu:
          // Voltmeter Menu code
          break;

      case AmmeterMenu:
          // Ammeter Menu code
          break;

      case OhmmeterMenu:
          // Ohmmeter Menu code
          break;

      case SigGenMenu:
          // Selection box and scroll bar
          oled.drawBitmap(0, 0, epd_bitmap_bg, SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_COLOR);
          // Signal Generator Menu code
          break;

      case ConfigMenu:
          // Config Menu code
          break;
  }

  oled.display(); // Update the display with the new content
  delay(50); // Optional: Delay for stability or to control the refresh rate
  /*
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
  */
}
