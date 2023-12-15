#include <SoftwareSerial.h>

// Define software serial pins on ESP8266
SoftwareSerial arduinoSerial(D4, D3); // RX, TX

void setup() {
  Serial.begin(9600);          // Serial monitor for debugging
  arduinoSerial.begin(9600);   // SoftwareSerial for Arduino Mega

  // Give some time for Arduino Mega to initialize
  delay(1000);
}

void loop() {
  // Check if there's data available from Arduino Mega
  if (arduinoSerial.available()) {
    // Read the command from Arduino Mega
    String command = arduinoSerial.readStringUntil('\n');

    // Process the command
    processCommand(command);
  }
}

void processCommand(String command) {
  // Print the received command to serial monitor
  Serial.println("Received command: " + command);

  // Respond back to Arduino Mega
  arduinoSerial.println("Hello mega");
}
