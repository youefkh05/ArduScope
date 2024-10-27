#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1      // Reset pin # (or -1 if sharing Arduino reset pin)

// Create an SSD1306 display object (I2C address is usually 0x3D or 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);   // device name is oled

#define SSD1306_I2C_ADDRESS 0x3D  // Set the I2C address
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LED1 12
#define LED2 7
#define LED3 6
#define LED4 5
//#define OLED_RESET (-1)

bool x = false;

// Define a bitmap for a signal generator icon, 16x16 pixels
const unsigned char sig_gen_bitmap[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x87,
    0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84,
    0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84,
    0x20, 0x84, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x00
};

void setup() {
    // Initialize the display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS)) { // Use the defined I2C address
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    display.clearDisplay();

    // Draw the bitmap at coordinates (x, y)
    display.drawBitmap(56, 24, sig_gen_bitmap, 16, 16, WHITE); // Centering the 16x16 bitmap

    // Show the display
    display.display();
}

void loop() {
  // Do nothing here
}