
#include <LwipEthernet.h>


#include <WiFiClient.h>
// #include <https
#include <ESP8266HTTPClient.h>



/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.

    This is Ethernet version of:
    https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino
*/


int CSPIN = 5;
ENC28J60lwIP eth(5);  // <== adapt to your hardware

// const char* host = "secure.onpremise.in";
const char* host = "https://secure.onpremise.in/";

const uint16_t port = 443;
//true finger print
const char fingerprint[] PROGMEM = "EE 95 61 06 FB 2C 72 4F 46 AA 7E 83 31 05 C6 18 9C 8D 31 42";
//flase finger print
// const char fingerprint[] PROGMEM = "EE 95 61 06 FB 2C 72 4F 46 AA 7E 83 31 05 C6 18 9C 8D 31 43";


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
  WiFiClientSecure client;
  // client.setInsecure();
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);
  HTTPClient https;

      Serial.print("[HTTPS] begin...\n");
    if (https.begin(client, host, port)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }

  // if (!client.connect(host, port)) {
  //   Serial.println("connection failed");
  //   delay(5000);
  //   return;
  // }

  // This will send a string to the server
  // Serial.println("sending data to server");
  // if (client.connected()) {  
  //   Serial.println("Client connected");
  //         Serial.println(" ok");
  //       Serial.println("Send GET request...");
  //        client.print("GET / HTTP/1.1\n");
  //       client.print("Host: secure.onpremise.in\n");
  //       client.print("Connection: close\n");
  //       client.print("\n"); }

  // // wait for data to be available
  // unsigned long timeout = millis();
  // while (client.available() == 0) {
  //   if (millis() - timeout > 5000) {
  //     Serial.println(">>> Client Timeout !");
  //     client.stop();
  //     delay(60000);
  //     return;
  //   }
  // }

  // // Read all the lines of the reply from server and print them to Serial
  // Serial.println("receiving from remote server");
  // client.sendAll(Serial);  // this peer closes once all data are sent

  // // Close the connection
  // Serial.println();
  // Serial.println("closing connection");
  // client.stop();

  delay(10000);  // execute once every 5 minutes, don't flood remote service
}
