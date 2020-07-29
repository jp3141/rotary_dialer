 
// For Teensy 3.x, or Teensy LC
// Choose 'USB Type' to be "Keyboard", or "Serial + Keyboard + ..."
// edit boards.txt and usb_desc.h to add Serial + Keyboard option

// Uses name.c to change USB name

#include "Keyboard.h"

//            ___      ___    ___
//____________| |______| |____| |______//_____
//     (L,     H)  (L,  H  (L, H)        N

const int LED = 13;
const int DialPin = 0; // connect dialer to upper top left pins (GND & pin 0)
unsigned long now, lastDialedTime;
unsigned int NPulses = 0;

void setup() {
  pinMode(LED, OUTPUT); digitalWrite(LED, LOW);
  pinMode(DialPin, INPUT_PULLUP); delay(1);
  Keyboard.begin();
  Serial.begin(9600);
  now = millis();
  while(!(Serial || ((millis()-now) > 10000) || digitalRead(DialPin))) { // flash LED for 10 s or until dial activates or serial port is opened
    digitalWrite(LED, HIGH); delay(3);
    digitalWrite(LED, LOW);  delay(100-3);
  }

  Serial.println("Compiled " __FILE__ " " __DATE__ " "  __TIME__);
  #include "printme.h"
  lastDialedTime = millis();
  Serial.print("> ");
}

void loop() {
  now = millis();
  while (!digitalRead(DialPin)) { // while pin is low 
    if ( ((millis()-now) > 100) && (NPulses > 0)) { // send keystroke if timeout and at least one pulse
      if ((millis()-lastDialedTime) > 5000) Serial.print(F("\n> "));
      lastDialedTime = millis();
      if (NPulses <= 10) { 
        Keyboard.print(NPulses % 10);
        Serial.print(NPulses % 10);      
      } // send it
      NPulses = 0;
    }
  } // loop until pulse starts ==> pin is not low
//  Serial.printf("%c3(%2i,", NPulses==0 ? '\n': ' ', millis()-now); now = millis();
  Serial.printf("%c(%2i,", NPulses ? ' ': '\n', millis()-now); now = millis();
  digitalWrite(LED, HIGH);   // pulse starts
  delay(5);  //debounce
  while (digitalRead(DialPin)); // loop while pulse is high
  Serial.printf("%2i) ",millis()-now);
  NPulses++; // count pulse  
  digitalWrite(LED, LOW);
  delay(5); //debounce falling edge
  
} 
