#include <U8g2lib.h>
#include <Wire.h>

// Initialize the display using U8g2 with I2C address 0x3D
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // U8G2_R0 is the rotation option


#define OLED_ADDRESS 0x3D  // Set the I2C address
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LED1 12
#define LED2 7
#define LED3 6
#define LED4 5

void draw(void) {
  // Set font and position for drawing
  
  u8g2.setFont(u8g2_font_unifont_t_symbols);  // Use a font compatible with U8g2
  u8g2.drawStr(0, 20, "Hello World!");        // Draw "Hello World!" at (0, 20)
  
}

void setup(void) {
  u8g2.setI2CAddress(OLED_ADDRESS << 1); // Shift address for the library
  u8g2.begin();  // Initialize the display
  
  // u8g2.setFlipMode(1); // Uncomment this if the display is upside down
}

void loop(void) {
  u8g2.firstPage();  
  do {
    draw();
  } while (u8g2.nextPage());
  
  delay(500);
}
