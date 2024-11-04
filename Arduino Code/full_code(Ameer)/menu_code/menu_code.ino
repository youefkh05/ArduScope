#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"
#include "bitmaps.h"
#include "application.h"
#include "Multi_Metre_Sig.h"
//#include "Osci.h"
#include "eerom_map.h"
//#include <stdint.h>
#include <stdlib.h>


// OLED display width and height, in pixels
//OLED Definitions
#define SCREEN_WIDTH      (128)   // OLED display width
#define SCREEN_HEIGHT     (64)    // OLED display height
#define OLED_RESET        (-1)    // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS  (0x3C)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);   // device name is oled
Adafruit_SH1106 oled(OLED_RESET);        // use this when SH1106

// Define constants for text size and color
#define TEXT_SIZE 1
#define TEXT_COLOR WHITE

// Function to draw a menu item
void drawMenuItem(int y_position, const char* item_text, const int index) {
    // Buffer to hold the bitmap read from EEPROM
    uint8_t bitmapBuffer[BIT_MAP_SIZE];
    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(26, y_position-8);
    oled.print(item_text);
    readBitmapFromEEPROM(bitmapBuffer, index, BIT_MAP_SIZE);
    //oled.drawBitmap(3, y_position - 13, item_bitmap, 16, 16, TEXT_COLOR); // Adjusted y position for bitmap
    oled.drawBitmap(3, y_position - 13,  bitmapBuffer, 16, 16, TEXT_COLOR); // Adjusted y position for bitmap
    delay(1);
    
}

char menu_items [6] [MAX_ITEM_LENGTH] = {
  {"Voltmeter"},
  {"Ammeter"},
  {"Ohmmeter"},
  {"Sig Gen"},
  {"Scope"},
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
uint8_t NUM_ITEMS = 6;

menus selected_menu = MainMenu;

uint8_t item_selected = 0; // which item in the menu is selected

uint8_t item_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
uint8_t item_sel_next; // next item - used in the menu screen to draw next item after the selected one

uint8_t device_selected = Voltmeter;
uint8_t range_selected = range1;
uint8_t mode_selected = DC_MODE;

float device_reading = 0;

void setup()
{
  MM_Init();
  Serial.begin(9600);

  //oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // select 3C or 3D (set your OLED I2C address)
  oled.begin(SH1106_SWITCHCAPVCC, OLED_I2C_ADDRESS);  // use this when SH1106 

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
  

  //Osci_Init();
}

void loop() 
{
  // Buffer to hold the bitmap read from EEPROM
  //uint8_t bitmapBuffer[BIT_MAP_SIZE];

  // Updates number of items according to selected menu
  switch (selected_menu)
  {
    case MainMenu:
    NUM_ITEMS = 6;
    break;
    
    case SigGenMenu:
    NUM_ITEMS = 4;

    case ConfigMenu:
    NUM_ITEMS = 2;

    default:
    NUM_ITEMS = 1;
  }
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

char reading_arr[MAX_ITEM_LENGTH];
itoa(device_reading, reading_arr,10); //Change reading to str to be printed on screen

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
              device_selected = Voltmeter;
              break;

            case 1:
              selected_menu = AmmeterMenu;
              device_selected = Ammeter;
              break;

            case 2:
              selected_menu = OhmmeterMenu;
              device_selected = Ohmeter;
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

/********************************************************************************/
      /*Signal Generator Selection*/

  if(selected_menu == SigGenMenu)
  {
    switch (item_selected)
          {
            case 0:
            break;

            case 1:
            break;

            case 2:
            break;

            case 3:
            break;
          }
  }
  
/**************************************************************************************************/
                /*OLED Main Menu*/
    oled.clearDisplay(); // Clear the display before drawing each frame
    switch (selected_menu)
    {
      case MainMenu:
        // Selection box and scroll bar
        oled.drawBitmap(0, 0, epd_bitmap_bg, SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_COLOR);

        // Draw Menu Items
        drawMenuItem(15, menu_items[item_sel_previous], item_sel_previous); // Menu Item 1
        drawMenuItem(37, menu_items[item_selected], item_selected);         // Menu Item 2
        drawMenuItem(59, menu_items[item_sel_next], item_sel_next);         // Menu Item 3

      break;

      case VoltmeterMenu:
      /*
      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(26,37, "Ammeter Reading");
      u8g.setFont(u8g_font_7x14);
      u8g.drawStr(26,59, reading_arr);
      */

      //Voltmeter Menu code
      oled.setTextSize(TEXT_SIZE);      // Keep default text size
      oled.setTextColor(WHITE);
      oled.setCursor(26, 37);           // Set position
      oled.print("Voltmeter Reading");  // Display text
      oled.setCursor(26, 59);           // Set position
      oled.print(reading_arr);          // Display text  

      break;

      case AmmeterMenu:
      //Osci_Run();

      //Ammeter Menu code
      oled.setTextSize(TEXT_SIZE);      // Keep default text size
      oled.setTextColor(WHITE);
      oled.setCursor(26, 37);           // Set position
      oled.print("Ammeter Reading");    // Display text
      oled.setCursor(26, 59);           // Set position
      oled.print(reading_arr);          // Display text
      
      break;

      case OhmmeterMenu:
      //Ohmmeter Menu Code
      oled.setTextSize(TEXT_SIZE);      // Keep default text size
      oled.setTextColor(WHITE);
      oled.setCursor(26, 37);           // Set position
      oled.print("Ohmmeter Reading");   // Display text
      oled.setCursor(26, 59);           // Set position
      oled.print(reading_arr);          // Display text

      break;

      case SigGenMenu:
      // Selection box and scroll bar
      oled.drawBitmap(0, 0, epd_bitmap_bg, SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_COLOR);
      //u8g.drawBitmapP(0, 0, 128/8, 64, epd_bitmap_bg);

        
        //Signal Generator Menu Code
        //Menu Item 1
        oled.setTextSize(TEXT_SIZE);                 // Keep default text size
        oled.setTextColor(WHITE);
        oled.setCursor(26, 15);                      // Set position
        oled.print(sig_menu_items[item_sel_previous]);   // Display text
        //u8g.setFont(u8g_font_7x14);
        //u8g.drawStr(26,15, sig_menu_items[item_sel_previous]);

        //Menu Item 2
        oled.setTextSize(TEXT_SIZE);                 // Keep default text size
        oled.setTextColor(WHITE);
        oled.setCursor(26, 37);                      // Set position
        oled.print(sig_menu_items[item_selected]);   // Display text

        //Menu Item 3
        oled.setTextSize(TEXT_SIZE);                 // Keep default text size
        oled.setTextColor(WHITE);
        oled.setCursor(26,59);                       // Set position
        oled.print(sig_menu_items[item_sel_next]);   // Display text

      break;

      case ConfigMenu:
      //Signal Generator Menu Code

      break;
    }
    
  oled.display(); // Update the display with the new content
  delay(50); // Optional: Delay for stability or to control the refresh rate

  
}
