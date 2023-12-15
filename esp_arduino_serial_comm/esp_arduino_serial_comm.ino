#include <SoftwareSerial.h>


SoftwareSerial nodeSerial(11,10); //Rx, Tx

void setup() {

Serial.begin(9600);

nodeSerial.begin(9600);

}

void loop() {

 delay(1000);

  // Send a command to ESP8266
  Serial.println("Sending a commond to node");
  nodeSerial.println("Hello ESP8266!");

  // Wait for a response from ESP8266
  while (!nodeSerial.available()) {
    delay(10);
    Serial.print('.');
  }

  // Read and print the response
  String response = nodeSerial.readStringUntil('\n');
  Serial.println("Response from ESP8266: " + response);
}

