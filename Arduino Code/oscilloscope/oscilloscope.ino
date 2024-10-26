#include "Osci.h"


extern Adafruit_SSD1306 oled;
// Range name table (those are stored in flash memory)
extern const char vRangeName[10][5] PROGMEM;
extern const char * const vstring_table[] PROGMEM;
extern const char hRangeName[10][6] PROGMEM;
extern const char * const hstring_table[] PROGMEM;
extern const PROGMEM float hRangeValue[];

extern int waveBuff[];        // wave form buffer (RAM remaining capacity is barely)
extern char chrBuff[];               // display string buffer
extern char hScale[];       // horizontal scale character
extern char vScale[];        // vartical scale

extern float lsb5;      // sensivity coefficient of 5V range. std=0.00563965 1.1*630/(1024*120)
extern float lsb50V;     // sensivity coefficient of 50V range. std=0.0512898 1.1*520.91/(1024*10.91)

extern volatile int vRange;           // V-range number 0:A50V,  1:A 5V,  2:50V,  3:20V,  4:10V,  5:5V,  6:2V,  7:1V,  8:0.5V,  9:0.2V
extern volatile int hRange;           // H-range nubmer 0:200ms, 1:100ms, 2:50ms, 3:20ms, 4:10ms, 5:5ms, 6;2ms, 7:1ms, 8:500us, 9;200us
extern volatile int trigD;            // trigger slope flag,     0:positive 1:negative
extern volatile int scopeP;           // operation scope position number. 0:Veratical, 1:Hrizontal, 2:Trigger slope
extern volatile boolean hold; // hold flag
extern volatile boolean switchPushed; // flag of switch pusshed !
extern volatile int saveTimer;        // remaining time for saving EEPROM
extern int timeExec;                  // approx. execution time of current range setting (ms)

extern int dataMin;                   // buffer minimum value (smallest=0)
extern int dataMax;                   //        maximum value (largest=1023)
extern int dataAve;                   // 10 x average value (use 10x value to keep accuracy. so, max=10230)
extern int rangeMax;                  // buffer value to graph full swing
extern int rangeMin;                  // buffer value of graph botto
extern int rangeMaxDisp;              // display value of max. (100x value)
extern int rangeMinDisp;              // display value if min.
extern int trigP;                     // trigger position pointer on data buffer
extern boolean trigSync;              // flag of trigger detected
extern int att10x;                    // 10x attenetor ON (effective when 1)

extern float waveFreq;                // frequency (Hz)
extern float waveDuty;                // duty ratio (%)

void setup() {
  pinMode(2, INPUT_PULLUP);             // button pussed interrupt (int.0 IRQ)
  pinMode(8, INPUT_PULLUP);             // Select button
  pinMode(9, INPUT_PULLUP);             // Up
  pinMode(10, INPUT_PULLUP);            // Down
  pinMode(11, INPUT_PULLUP);            // Hold
  pinMode(12, INPUT);                   // 1/10 attenuator(Off=High-Z, Enable=Output Low)
  pinMode(13, OUTPUT);                  // LED

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // select 3C or 3D (set your OLED I2C address)
  //oled.begin(SH1106_SWITCHCAPVCC, 0x3D);  // use this when SH1106 

  auxFunctions();                       // Voltage measure (never return)
  loadEEPROM();                         // read last settings from EEPROM
  analogReference(INTERNAL);            // ADC full scale = 1.1V
  attachInterrupt(0, pin2IRQ, FALLING); // activate IRQ at falling edge mode
  startScreen();                        // display start message
}

void loop() {
  setConditions();                      // set measurment conditions
  digitalWrite(13, HIGH);               // flash LED
  readWave();                           // read wave form and store into buffer memory
  digitalWrite(13, LOW);                // stop LED
  setConditions();                      // set measurment conditions again (reflect change during measure)
  dataAnalize();                        // analize data
  writeCommonImage();                   // write fixed screen image (2.6ms)
  plotData();                           // plot waveform (10-18ms)
  dispInf();                            // display information (6.5-8.5ms)
  oled.display();                       // send screen buffer to OLED (37ms)
  saveEEPROM();                         // save settings to EEPROM if necessary
  while (hold == true) {                // wait if Hold flag ON
    dispHold();
    delay(10);
  }                                     // loop cycle speed = 60-470ms (buffer size = 200)
}
