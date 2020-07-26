
// For Teensy 3.x, or Teensy LC
//Choose 'USB Type' to be "Keyboard", or "Serial + Keybaord + ..."
#include "Keyboard.h"

int led = 13;
int DialPin = 0;
unsigned long now, lastDialed;
int NPulses = 0;
int PulseStarted = 0;


void setup() {
  pinMode(led, OUTPUT); digitalWrite(led, LOW);
  pinMode(DialPin, INPUT_PULLUP); delay(1);
  Keyboard.begin();
  Serial.begin(9600);
  now = millis();
  while(!Serial && ((millis()-now) < 10000) && !digitalRead(DialPin)) {
    digitalWrite(led, HIGH);
    delay(10);
    digitalWrite(led, LOW);
    delay(90);
  }

  Serial.println("Compiled " __FILE__ " " __DATE__ " "  __TIME__);
  lastDialed = millis();
  Serial.print("> ");
}

void loop() {
  while (!digitalRead(DialPin));  // loop until pulse starts
  NPulses++;  // increment counter at start of pulse
  now = millis();
  digitalWrite(led, LOW);
  delay(5);  //debounce
  while ((millis()-now) < 100) {
    if (!digitalRead(DialPin)) {
      digitalWrite(led, HIGH);   // pulse ended
      break;   // loop until pin is 0 or 100 ms
    } // if
  } // while
// pin is low now, or stuck high for over 100 ms
  delay(5); //debounce falling edge

  PulseStarted = 0;
  while ((millis()-now) < 150) { // now wait for 150 ms timeout, or start of next pulse
    if (digitalRead(DialPin)) {  // start of next pulse
      PulseStarted = 1;
      break;   // got another pulse starting -- back to beginning.
    }
  } // end of while -- either timeout or pulse started
  if (!PulseStarted) {
    digitalWrite(led, LOW);
    if ((millis()-lastDialed) > 5000) Serial.print("\n> ");
    lastDialed = millis();
    if (NPulses <= 10) { 
      Keyboard.print(NPulses % 10);
      Serial.print(NPulses % 10);      
    }
    NPulses = 0;
  } // if
  
} 
