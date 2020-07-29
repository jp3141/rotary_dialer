Serial.println("\
 \n\
// For Teensy 3.x, or Teensy LC\n\
// Choose 'USB Type' to be \"Keyboard\", or \"Serial + Keyboard + ...\"\n\
// edit boards.txt and usb_desc.h to add Serial + Keyboard option\n\
\n\
// Uses name.c to change USB name\n\
\n\
#include \"Keyboard.h\"\n\
\n\
//            ___      ___    ___\n\
//____________| |______| |____| |______//_____\n\
//     (L,     H)  (L,  H  (L, H)        N\n\
\n\
const int LED = 13;\n\
const int DialPin = 0; // connect dialer to upper top left pins (GND & pin 0)\n\
unsigned long now, lastDialedTime;\n\
unsigned int NPulses = 0;\n\
\n\
void setup() {\n\
  pinMode(LED, OUTPUT); digitalWrite(LED, LOW);\n\
  pinMode(DialPin, INPUT_PULLUP); delay(1);\n\
  Keyboard.begin();\n\
  Serial.begin(9600);\n\
  now = millis();\n\
  while(!(Serial || ((millis()-now) > 10000) || digitalRead(DialPin))) { // flash LED for 10 s or until dial activates or serial port is opened\n\
    digitalWrite(LED, HIGH); delay(3);\n\
    digitalWrite(LED, LOW);  delay(100-3);\n\
  }\n\
\n\
  Serial.println(\"Compiled \" __FILE__ \" \" __DATE__ \" \"  __TIME__);\n\
  #include \"printme.h\"\n\
  lastDialedTime = millis();\n\
  Serial.print(\"> \");\n\
}\n\
\n\
void loop() {\n\
  now = millis();\n\
  while (!digitalRead(DialPin)) { // while pin is low \n\
    if ( ((millis()-now) > 100) && (NPulses > 0)) { // send keystroke if timeout and at least one pulse\n\
      if ((millis()-lastDialedTime) > 5000) Serial.print(F(\"\\n> \"));\n\
      lastDialedTime = millis();\n\
      if (NPulses <= 10) { \n\
        Keyboard.print(NPulses % 10);\n\
        Serial.print(NPulses % 10);      \n\
      } // send it\n\
      NPulses = 0;\n\
    }\n\
  } // loop until pulse starts ==> pin is not low\n\
//  Serial.printf(\"%c3(%2i,\", NPulses==0 ? '\\n': ' ', millis()-now); now = millis();\n\
  Serial.printf(\"%c(%2i,\", NPulses ? ' ': '\\n', millis()-now); now = millis();\n\
  digitalWrite(LED, HIGH);   // pulse starts\n\
  delay(5);  //debounce\n\
  while (digitalRead(DialPin)); // loop while pulse is high\n\
  Serial.printf(\"%2i) \",millis()-now);\n\
  NPulses++; // count pulse  \n\
  digitalWrite(LED, LOW);\n\
  delay(5); //debounce falling edge\n\
  \n\
} \n\
");
