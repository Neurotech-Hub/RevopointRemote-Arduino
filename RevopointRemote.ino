#include <IRremote.h>

const int irSendPin = A0; // Pin connected to the IR LED
IRsend irsend;

unsigned long necCodes[] = {
  0x00FF20DF,  // 0 CW 
  0x00FF609F,  // 1 CCW
  0x00FF906F,  // 2 STOP/START
  0x00FF30CF,  // 3 SPEED UP
  0x00FF708F,  // 4 SLOW DOWN
  0x00FF8877,  // 5 SAVE
};

void setup() {
  Serial.begin(9600);
  irsend.begin(irSendPin); // Initialize the IR sender with the correct pin
}

void loop() {
  if (Serial.available() > 0) {
    int index = Serial.parseInt(); // Read the input number as an index

    if (index >= 0 && index < sizeof(necCodes) / sizeof(necCodes[0])) {
      irsend.sendNEC(necCodes[index], 32); // Send NEC code
      Serial.print("Sent code: 0x");
      Serial.println(necCodes[index], HEX);
    } else {
      Serial.println("Invalid index. Please enter a number between 0 and 7.");
    }

    // Clear the input buffer
    while (Serial.available()) {
      Serial.read();
    }
  }
}
