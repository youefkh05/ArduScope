
#include "Multi_Metre.h"


void setup() {
  // Set the pins as output
  pinMode(A_MUX_1, OUTPUT);
  pinMode(A_MUX_2, OUTPUT);
}

void loop()
{
    // Blink A_MUX_1
  digitalWrite(A_MUX_1, HIGH); // Turn on A_MUX_1
  delay(1000);                 // Wait for 1 second
  digitalWrite(A_MUX_1, LOW);  // Turn off A_MUX_1

  // Blink A_MUX_2
  digitalWrite(A_MUX_2, HIGH); // Turn on A_MUX_2
  delay(1000);                 // Wait for 1 second
  digitalWrite(A_MUX_2, LOW);  // Turn off A_MUX_2

  // Wait a second before repeating
  delay(1000);
}
