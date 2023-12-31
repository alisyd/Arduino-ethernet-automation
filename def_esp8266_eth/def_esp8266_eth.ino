/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.

    This is Ethernet version of:
    https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino
*/

#include <LwipEthernet.h>

// Wiznet5500lwIP eth(/*SS*/ 16);  // <== adapt to your hardware
#define CSPIN 5
ENC28J60lwIP eth(CSPIN);
const char* host = "www.google.com";
const uint16_t port = 443;

void setup() {
  Serial.begin(115200);

  Serial.println("\nEthernet\n");

  // 1. Currently when no default is set, esp8266-Arduino uses the first
  //    DHCP client interface receiving a valid address and gateway to
  //    become the new lwIP default interface.
  // 2. Otherwise - when using static addresses - lwIP for every packets by
  //    defaults selects automatically the best suited output interface
  //    matching the destination address.  If several interfaces match,
  //    the first one is picked.  On esp8266/Arduno: WiFi interfaces are
  //    checked first.
  // 3. Or, use `::setDefault()` to force routing through this interface.
  // eth.setDefault(); // default route set through this interface

  if (!ethInitDHCP(eth)) {
    Serial.printf("no hardware found\n");
    while (1) {
      delay(1000);
    }
  }

  while (!eth.connected()) {
    Serial.printf(".");
    delay(1000);
  }

  Serial.printf("Ethernet: IP Address: %s\n",
                eth.localIP().toString().c_str());
}

void loop() {

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  Serial.printf("Link sense: %d (detectable: %d)\n", eth.isLinked(), eth.isLinkDetectable());

  // Use WiFiClient class to create TCP connections
  // (this class could have been named TCPClient)
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) { client.println("hello from ESP8266"); }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  client.sendAll(Serial);  // this peer closes once all data are sent

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(300000);  // execute once every 5 minutes, don't flood remote service
}
