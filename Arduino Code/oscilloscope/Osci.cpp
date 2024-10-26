#include "Osci.h"

#define MAX_VRANGE      (5)
#define MAX_HRANGE      (6)
#define LSB_5V          (0.00566826f)  // Sensitivity coefficient of 5V range. std=0.00563965, 1.1*630/(1024*120)
//float LSB_5V = 0.00566826;      // sensivity coefficient of 5V range. std=0.00563965 1.1*630/(1024*120)
//float lsb50V = 0.05243212;     // sensivity coefficient of 50V range. std=0.0512898 1.1*520.91/(1024*10.91)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);   // device name is oled
//Adafruit_SH1106 oled(OLED_RESET);        // use this when SH1106

// Range name table (those are stored in flash memory)
//const char vRangeName[10][5] PROGMEM = {"A50V", "A 5V", " 50V", " 20V", " 10V", "  5V", "  2V", "  1V", "0.5V", "0.2V"}; // Vertical display character (number of characters including \ 0 is required)
const char vstring_table[MAX_VRANGE] [5] PROGMEM = { "  5V", "  2V", "  1V", "0.5V", "0.2V"};
//const char hRangeName[10][6] PROGMEM = {"200ms", "100ms", " 50ms", " 20ms", " 10ms", "  5ms", "  2ms", "  1ms", "500us", "200us"};  //  Hrizontal display characters
const char hstring_table[MAX_HRANGE] [6] PROGMEM = {"200ms", " 50ms", " 10ms", "  2ms", "500us", "200us"};
const PROGMEM float hRangeValue[] = { 0.2, 0.05, 0.01, 0.002, 0.5e-3, 0.2e-3}; // horizontal range value in second. ( = 25pix on screen)

int waveBuff[REC_LENG];        // wave form buffer (RAM remaining capacity is barely)
char chrBuff[8];               // display string buffer
char hScale[] = "xxxAs";       // horizontal scale character
char vScale[] = "xxxx";        // vartical scale

volatile char vRange;                   // V-range number 0:5V,   1:2V,  2:1V,  3:0.5V,  4:0.2V
volatile char hRange;                   // H-range nubmer 0:200ms,  1:50ms, 2:10ms, 3;2ms, 4:500us, 5;200us
//volatile char trigD;                  // trigger slope flag,     0:positive 1:negative
volatile boolean scopeP;                // operation scope position number. 0:Veratical, 1:Hrizontal, 2:Trigger slope
volatile boolean hold = false;          // hold flag
volatile boolean switchPushed = false;  // flag of switch pusshed !
//volatile int saveTimer;               // remaining time for saving EEPROM
//int timeExec;                         // approx. execution time of current range setting (ms)

int dataMin;                   // buffer minimum value (smallest=0)
int dataMax;                   //        maximum value (largest=1023)
int dataAve;                   // 10 x average value (use 10x value to keep accuracy. so, max=10230)
int rangeMax;                  // buffer value to graph full swing
int rangeMin;                  // buffer value of graph botto
int rangeMaxDisp;              // display value of max. (100x value)
int rangeMinDisp;              // display value if min.
int trigP;                     // trigger position pointer on data buffer
boolean trigSync;              // flag of trigger detected
//int att10x;                    // 10x attenetor ON (effective when 1)

float waveFreq;                // frequency (Hz)
int waveDuty;                // duty ratio (%)

void Osci_Init(void)
{
  pinMode(Osci_Input_Bot, INPUT_PULLUP);             // button pussed interrupt (int.0 IRQ)
  pinMode(Select_Bot, INPUT_PULLUP);          // Select button
  pinMode(Up_Bot , INPUT_PULLUP);             // Up
  pinMode(Down_Bot, INPUT_PULLUP);            // Down
  pinMode(Hold_Bot, INPUT_PULLUP);            // Hold
  //pinMode(12, INPUT);                   // 1/10 attenuator(Off=High-Z, Enable=Output Low)


  oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // select 3C or 3D (set your OLED I2C address)
  //oled.begin(SH1106_SWITCHCAPVCC, 0x3D);  // use this when SH1106 

  //auxFunctions();                       // Voltage measure (never return)
  //loadEEPROM();                         // read last settings from EEPROM
  analogReference(INTERNAL);            // ADC full scale = 1.1V
  attachInterrupt(0, pin2IRQ, FALLING); // activate IRQ at falling edge mode

   vRange=1;             // V-range number 0:5V,   1:2V,  2:1V,  3:0.5V,  4:0.2V
   hRange=1;             // H-range nubmer 0:200ms,  1:50ms, 2:10ms, 3;2ms, 4:500us, 5;200us
   //trigD=1;            // trigger slope flag,     0:positive 1:negative
   scopeP=false;
}


void Osci_Run(void) {
  startScreen(); // display start message
  while(1){
    setConditions();                      // set measurment conditions
    readWave();                           // read wave form and store into buffer memory
    setConditions();                      // set measurment conditions again (reflect change during measure)
    dataAnalize();                        // analize data
    writeCommonImage();                   // write fixed screen image (2.6ms)
    plotData();                           // plot waveform (10-18ms)
    dispInf();                            // display information (6.5-8.5ms)
    oled.display();                       // send screen buffer to OLED (37ms)
    //saveEEPROM();                       // save settings to EEPROM if necessary
    while (hold == true) {                // wait if Hold flag ON
      dispHold();
      delay(10);                          // loop cycle speed = 60-470ms (buffer size = 200)
    }       
                                  
  }                        
   
}

static void setConditions() {           // measuring condition setting
  // get range name from PROGMEM
  strcpy_P(hScale, hstring_table[hRange]);  // H range name
  strcpy_P(vScale, vstring_table[vRange]);  // Directly read from PROGMEM

  switch (vRange) {              // setting of Vrange
    case 0: {                    // 5V range
        rangeMax = 5 / LSB_5V;    // set full scale pixcel count number
        rangeMaxDisp = 500;
        rangeMin = 0;
        rangeMinDisp = 0;
        //att10x = 0;              // no input attenuator
        break;
      }
    case 1: {                    // 2V range
        rangeMax = 2 / LSB_5V;    // set full scale pixcel count number
        rangeMaxDisp = 200;
        rangeMin = 0;
        rangeMinDisp = 0;
        //att10x = 0;              // no input attenuator
        break;
      }
    case 2: {                    // 1V range
        rangeMax = 1 / LSB_5V;    // set full scale pixcel count number
        rangeMaxDisp = 100;
        rangeMin = 0;
        rangeMinDisp = 0;
        //att10x = 0;              // no input attenuator
        break;
      }
    case 3: {                    // 0.5V range
        rangeMax = 0.5 / LSB_5V;  // set full scale pixcel count number
        rangeMaxDisp = 50;
        rangeMin = 0;
        rangeMinDisp = 0;
        //att10x = 0;              // no input attenuator
        break;
      }
    case 4: {                    // 0.5V range
        rangeMax = 0.2 / LSB_5V;  // set full scale pixcel count number
        rangeMaxDisp = 20;
        rangeMin = 0;
        rangeMinDisp = 0;
        //att10x = 0;              // no input attenuator
        break;
      }
  }
}

static void writeCommonImage() {                 // Common screen image drawing
  oled.clearDisplay();                    // erase all(0.4ms)
  oled.setTextColor(WHITE);               // write in white character
  oled.setCursor(85, 0);                  // Start at top-left corner
  oled.println(F("av    v"));             // 1-st line fixed characters
  oled.drawFastVLine(26, 9, 55, WHITE);   // left vartical line
  oled.drawFastVLine(127, 9, 3, WHITE);   // right vrtical line up
  oled.drawFastVLine(127, 61, 3, WHITE);  // right vrtical line bottom

  oled.drawFastHLine(24, 9, 7, WHITE);    // Max value auxiliary mark
  oled.drawFastHLine(24, 36, 2, WHITE);
  oled.drawFastHLine(24, 63, 7, WHITE);

  oled.drawFastHLine(51, 9, 3, WHITE);    // Max value auxiliary mark
  oled.drawFastHLine(51, 63, 3, WHITE);

  oled.drawFastHLine(76, 9, 3, WHITE);    // Max value auxiliary mark
  oled.drawFastHLine(76, 63, 3, WHITE);

  oled.drawFastHLine(101, 9, 3, WHITE);   // Max value auxiliary mark
  oled.drawFastHLine(101, 63, 3, WHITE);

  oled.drawFastHLine(123, 9, 5, WHITE);   // right side Max value auxiliary mark
  oled.drawFastHLine(123, 63, 5, WHITE);

  for (int x = 26; x <= 128; x += 5) {
    oled.drawFastHLine(x, 36, 2, WHITE);  // Draw the center line (horizontal line) with a dotted line
  }
  for (int x = (127 - 25); x > 30; x -= 25) {
    for (int y = 10; y < 63; y += 5) {
      oled.drawFastVLine(x, y, 2, WHITE); // Draw 3 vertical lines with dotted lines
    }
  }
}

static void readWave() {                            // Record waveform to memory array
  
  //if (att10x == 1) {                         // if 1/10 attenuator required
    //pinMode(12, OUTPUT);                     // assign attenuator controle pin to OUTPUT,
    //digitalWrite(12, LOW);                   // and output LOW (output 0V)
  //} else {                                   // if not required
    //pinMode(12, INPUT);                      // assign the pin input (Hi-z)
  //}
  switchPushed = false;                      // Clear switch operation flag
  ADCSRA = ADCSRA & 0xf8;
  switch (hRange) {                          // set recording conditions in accordance with the range number
    case 0: {                                // 200ms range
        //timeExec = 1600 + 60;                // Approximate execution time(ms) Used for countdown until saving to EEPROM
        ADCSRA = ADCSRA | 0x07;              // dividing ratio = 128 (default of Arduino）
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 112us
          delayMicroseconds(7888);           // timing adjustment
          if (switchPushed == true) {        // if any switch touched
            switchPushed = false;
            break;                           // abandon record(this improve response)
          }
        }
        break;
      }
    case 1: {                                // 50ms range
        //timeExec = 400 + 60;                 // Approximate execution time(ms)
        ADCSRA = ADCSRA | 0x07;              // dividing ratio = 128 (default of Arduino）
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 112us
          // delayMicroseconds(1888);           // timing adjustmet
          delayMicroseconds(1880);           // timing adjustmet tuned

          if (switchPushed == true) {        // if any switch touched
            break;                           // abandon record(this improve response)
          }
        }
        break;
      }
    case 2: {                                // 10ms range
        //timeExec = 80 + 60;                  // Approximate execution time(ms)
        ADCSRA = ADCSRA | 0x07;              // dividing ratio = 128 (default of Arduino）
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 112us
          // delayMicroseconds(288);            // timing adjustmet
          delayMicroseconds(287);            // timing adjustmet tuned
          if (switchPushed == true) {        // if any switch touched
            break;                           // abandon record(this improve response)
          }
        }
        break;
      }
    case 3: {                                // 2ms range
        //timeExec = 16 + 60;                  // Approximate execution time(ms)
        ADCSRA = ADCSRA | 0x06;              // dividing ratio = 64 (0x1=2, 0x2=4, 0x3=8, 0x4=16, 0x5=32, 0x6=64, 0x7=128)
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 56us
          // delayMicroseconds(24);             // timing adjustmet
          delayMicroseconds(23);             // timing adjustmet tuned
        }
        break;
      }
    case 4: {                                // 500us range
        //timeExec = 4 + 60;                   // Approximate execution time(ms)
        ADCSRA = ADCSRA | 0x04;              // dividing ratio = 16(0x1=2, 0x2=4, 0x3=8, 0x4=16, 0x5=32, 0x6=64, 0x7=128)
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 16us
          delayMicroseconds(4);              // timing adjustmet
          // time fine adjustment 0.0625 x 8 = 0.5us（nop=0.0625us @16MHz)
          asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        }
        break;
      }
    case 5: {                                // 200us range
        //timeExec = 2 + 60;                   // Approximate execution time(ms)
        ADCSRA = ADCSRA | 0x02;              // dividing ratio = 4(0x1=2, 0x2=4, 0x3=8, 0x4=16, 0x5=32, 0x6=64, 0x7=128)
        for (int i = 0; i < REC_LENG; i++) { // up to rec buffer size
          waveBuff[i] = analogRead(Osci_In);       // read and save approx 6us
          // time fine adjustment 0.0625 * 20 = 1.25us (nop=0.0625us @16MHz)
          asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
          asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        }
        break;
      }
  }
}

static void dataAnalize() {                       // get various information from wave form
  int d;
  long sum = 0;

  // search max and min value
  dataMin = 1023;                          // min value initialize to big number
  dataMax = 0;                             // max value initialize to small number
  for (int i = 0; i < REC_LENG; i++) {     // serach max min value
    d = waveBuff[i];
    sum = sum + d;
    if (d < dataMin) {                     // update min
      dataMin = d;
    }
    if (d > dataMax) {                     // updata max
      dataMax = d;
    }
  }

  // calculate average
  dataAve = (sum + 10) / 20;               // Average value calculation (calculated by 10 times to improve accuracy)

  // Trigger position search
  for (trigP = ((REC_LENG / 2) - 51); trigP < ((REC_LENG / 2) + 50); trigP++) { // Find the points that straddle the median at the center ± 50 of the data range
      // if trigger direction is positive
      if ((waveBuff[trigP - 1] < (dataMax + dataMin) / 2) && (waveBuff[trigP] >= (dataMax + dataMin) / 2)) {
        break;                                    // positive trigger position found !
      }
    
  }
  trigSync = true;
  if (trigP >= ((REC_LENG / 2) + 50)) {           // If the trigger is not found in range
    trigP = (REC_LENG / 2);                       // Set it to the center for the time being
    trigSync = false;                             // set Unsync display flag
  }
  if ((dataMax - dataMin) <= MIN_TRIG_SWING) {    // amplitude of the waveform smaller than the specified value
    trigSync = false;                             // set Unsync display flag
  }
  freqDuty();
}

static void freqDuty() {                               // detect frequency and duty cycle value from waveform data
  int swingCenter;                              // center of wave (half of p-p)
  float p0 = 0;                                 // 1-st posi edge
  float p1 = 0;                                 // total length of cycles
  int p2 = 0;                                 // total length of pulse high time
  float pFine = 0;                              // fine position (0-1.0)
  float lastPosiEdge;                           // last positive edge position

  float pPeriod;                                // pulse period
  float pWidth;                                 // pulse width

  int p1Count = 0;                              // wave cycle count
  int p2Count = 0;                              // High time count

  boolean a0Detected = false;
  //  boolean b0Detected = false;
  boolean posiSerch = true;                      // true when serching posi edge

  swingCenter = (3 * (dataMin + dataMax)) / 2;   // calculate wave center value

  for (int i = 1; i < REC_LENG - 2; i++) {       // scan all over the buffer
    if (posiSerch == true) {   // posi slope (frequency serch)
      if ((sum3(i) <= swingCenter) && (sum3(i + 1) > swingCenter)) {  // if across the center when rising (+-3data used to eliminate noize)
        pFine = (float)(swingCenter - sum3(i)) / ((swingCenter - sum3(i)) + (sum3(i + 1) - swingCenter) );  // fine cross point calc.
        if (a0Detected == false) {               // if 1-st cross
          a0Detected = true;                     // set find flag
          p0 = i + pFine;                        // save this position as startposition
        } else {
          p1 = i + pFine - p0;                   // record length (length of n*cycle time)
          p1Count++;
        }
        lastPosiEdge = i + pFine;                // record location for Pw calcration
        posiSerch = false;
      }
    } else {   // nega slope serch (duration serch)
      if ((sum3(i) >= swingCenter) && (sum3(i + 1) < swingCenter)) {  // if across the center when falling (+-3data used to eliminate noize)
        pFine = (float)(sum3(i) - swingCenter) / ((sum3(i) - swingCenter) + (swingCenter - sum3(i + 1)) );
        if (a0Detected == true) {
          p2 = p2 + (i + pFine - lastPosiEdge);  // calucurate pulse width and accumurate it
          p2Count++;
        }
        posiSerch = true;
      }
    }
  }

  pPeriod = p1 / p1Count;                 // pulse period
  pWidth = p2 / p2Count;                  // palse width

  waveFreq = 1.0 / ((pgm_read_float(hRangeValue + hRange) * pPeriod) / 25.0); // frequency
  waveDuty = 100.0 * pWidth / pPeriod;                                      // duty ratio
}

static int sum3(int k) {       // Sum of before and after and own value
  int m = waveBuff[k - 1] + waveBuff[k] + waveBuff[k + 1];
  return m;
}

static void startScreen() {                      // Staru up screen
  oled.clearDisplay();
  oled.setTextSize(1);                    // at double size character
  oled.setTextColor(WHITE);
  oled.setCursor(40, 0);
  oled.println(F("ArduScope"));  
  oled.setCursor(30, 20);
  oled.println(F("Oscilloscope")); 
  oled.setCursor(55, 42);            
  oled.println(F(";)"));                
  oled.display();                         
  delay(1500);
  oled.clearDisplay();
  oled.setTextSize(1);                    // After this, standard font size
}

static void dispHold() {                         // display "Hold"
  oled.fillRect(42, 11, 24, 8, BLACK);    // black paint 4 characters
  oled.setCursor(42, 11);
  oled.print(F("Hold"));                  // Hold
  oled.display();                         //
}

static void dispInf() {                          // Display of various information
  float voltage;
  // display vertical sensitivity
  oled.setCursor(2, 0);                   // around top left
  oled.print(vScale);                     // vertical sensitivity value
  if (scopeP == false) {                      // if scoped
    oled.drawFastHLine(0, 7, 27, WHITE);  // display scoped mark at the bottom
    oled.drawFastVLine(0, 5, 2, WHITE);
    oled.drawFastVLine(26, 5, 2, WHITE);
  }

  // horizontal sweep speed
  oled.setCursor(34, 0);                  //
  oled.print(hScale);                     // display sweep speed (time/div)
  if (scopeP == true) {                      // if scoped
    oled.drawFastHLine(32, 7, 33, WHITE); // display scoped mark at the bottom
    oled.drawFastVLine(32, 5, 2, WHITE);
    oled.drawFastVLine(64, 5, 2, WHITE);
  }

  // trigger polarity
  oled.setCursor(75, 0);                  // at top center
  oled.print(char(0x18));                 // up mark

  // average voltage
  voltage = dataAve * LSB_5V / 10.0;          // 5V range value
  if (voltage < 10.0) {                      // if less than 10V
    dtostrf(voltage, 4, 2, chrBuff);         // format x.xx
  } else {                                   // no!
    dtostrf(voltage, 4, 1, chrBuff);         // format xx.x
  }
  oled.setCursor(98, 0);                     // around the top right
  oled.print(chrBuff);                       // display average voltage圧の平均値を表示
  //  oled.print(saveTimer);                 // use here for debugging

  // vartical scale lines
  voltage = rangeMaxDisp / 100.0;            // convart Max voltage
  dtostrf(voltage, 4, 2, chrBuff);
  oled.setCursor(0, 9);
  oled.print(chrBuff);                       // display Max value

  voltage = (rangeMaxDisp + rangeMinDisp) / 200.0; // center value calculation
  dtostrf(voltage, 4, 2, chrBuff);
  oled.setCursor(0, 33);
  oled.print(chrBuff);                       // display the value

  voltage = rangeMinDisp / 100.0;            // convart Min vpltage
  dtostrf(voltage, 4, 2, chrBuff);
  oled.setCursor(0, 57);
  oled.print(chrBuff);                       // display the value

  // display frequency, duty % or trigger missed
  if (trigSync == false) {                   // If trigger point can't found
    oled.fillRect(92, 14, 24, 8, BLACK);     // black paint 4 character
    oled.setCursor(92, 14);                  //
    oled.print(F("unSync"));                 // dosplay Unsync
  } else {
    oled.fillRect(90, 12, 25, 9, BLACK);    // erase Freq area
    oled.setCursor(91, 13);                  // set display locatio
    if (waveFreq < 100.0) {                  // if less than 100Hz
      oled.print(waveFreq, 1);               // display 99.9Hz
      oled.print(F("Hz"));
    } else if (waveFreq < 1000.0) {          // if less than 1000Hz
      oled.print(waveFreq, 0);               // display 999Hz
      oled.print(F("Hz"));
    } else if (waveFreq < 10000.0) {         // if less than 10kHz
      oled.print((waveFreq / 1000.0), 2);    // display 9.99kH
      oled.print(F("kH"));
    } else {                                 // if more
      oled.print((waveFreq / 1000.0), 1);    // display 99.9kH
      oled.print(F("kH"));
    }
    oled.fillRect(96, 21, 25, 10, BLACK);    // erase Freq area (as small as possible)
    oled.setCursor(105, 23);                  // set location
    oled.print(waveDuty, 1);                 // display duty (High level ratio) in %
    oled.print(F("%"));
  }
}

static void plotData() {                    // plot wave form on OLED
  long y1, y2;
  for (int x = 0; x <= 98; x++) {
    y1 = map(waveBuff[x + trigP - 50], rangeMin, rangeMax, 63, 9); // convert to plot address
    y1 = constrain(y1, 9, 63);                                     // Crush(Saturate) the protruding part
    y2 = map(waveBuff[x + trigP - 49], rangeMin, rangeMax, 63, 9); // to address calucurate
    y2 = constrain(y2, 9, 63);                                     //
    oled.drawLine(x + 27, y1, x + 28, y2, WHITE);                  // connect between point
  }
}
/*
static void saveEEPROM() {                    // Save the setting value in EEPROM after waiting a while after the button operation.
  if (saveTimer > 0) {                 // If the timer value is positive,
    saveTimer = saveTimer - timeExec;  // Timer subtraction
    if (saveTimer < 0) {               // if time up
      EEPROM.write(0, vRange);         // save current status to EEPROM
      EEPROM.write(1, hRange);
      EEPROM.write(2, trigD);
      EEPROM.write(3, scopeP);
    }
  }
}

static void loadEEPROM() {                    // Read setting values from EEPROM (abnormal values will be corrected to default)
  int x;
  x = EEPROM.read(0);                  // vRange
  if ((x < 0) || (7 < x)) {            // if out side 0-9
    x = 3;                             // default value
  }
  vRange = x;

  x = EEPROM.read(1);                  // hRange
  if ((x < 0) || (9 < x)) {            // if out of 0-9
    x = 3;                             // default value
  }
  hRange = x;
  x = EEPROM.read(2);                  // trigD
  if ((x < 0) || (1 < x)) {            // if out of 0-1
    x = 1;                             // default value
  }
  trigD = x;
  x = EEPROM.read(3);                  // scopeP
  if ((x < 0) || (2 < x)) {            // if out of 0-2
    x = 1;                             // default value
  }
  scopeP = x;
}
*/



static void uuPinOutputLow(unsigned int d, unsigned int a) { // 指定ピンを出力、LOWに設定
  // PORTx =0, DDRx=1
  unsigned int x;
  x = d & 0x00FF; PORTD &= ~x; DDRD |= x;
  x = d >> 8;     PORTB &= ~x; DDRB |= x;
  x = a & 0x003F; PORTC &= ~x; DDRC |= x;
}

static void pin2IRQ() {                   // Pin2(int.0) interrupr handler
  // Pin8,9,10,11 buttons are bundled with diodes and connected to Pin2.
  // So, if any button is pressed, this routine will start.
  int x;                           // Port information holding variable

  x = PINB;                        // read port B status
  if ( (x & 0x07) != 0x07) {       // if bottom 3bit is not all Hi(any wer pressed)
    //saveTimer = 5000;              // set EEPROM save timer to 5 secnd
    switchPushed = true;           // switch pushed falag ON
  }
  if ((x & 0x01) == 0) {           // if select button(Pin8) pushed,
    scopeP=!scopeP;                      // forward scope position
  }

  if ((x & 0x02) == 0) {           // if UP button(Pin9) pusshed, and
    if (scopeP == false) {             // scoped vertical range
      vRange++;                    // V-range up !
      if (vRange > (MAX_VRANGE-1)) {            // if upper limit
        vRange = MAX_VRANGE-1;                // stay as is
      }
    }
    if (scopeP == true) {             // if scoped hrizontal range
      hRange++;     
                     // H-range up !
      if (hRange > (MAX_HRANGE-1)) {            // if upper limit
        hRange = MAX_HRANGE-1;                // stay as is
      }
    }
  }

  if ((x & 0x04) == 0) {           // if DOWN button(Pin10) pusshed, and
    if (scopeP == false) {             // scoped vertical range
      vRange--;                    // V-range DOWN
      if (vRange < 0) {            // if bottom
        vRange = 0;                // stay as is
      }
    }
    if (scopeP == true) {             // if scoped hrizontal range
      hRange--;                    // H-range DOWN
      if (hRange < 0) {            // if bottom
        hRange = 0;                // satay as is
      }
    }
  }

  if ((x & 0x08) == 0) {           // if HOLD button(pin11) pushed
    hold = ! hold;                 // revers the flag
  }
}







