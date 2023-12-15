/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

// #include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "certs.h"
#include <UIPEthernet.h>
int eth_cs = 5;
int next;

uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
char SERIAL_NO[] = "AXTCP101";


// #ifndef STASSID
// #define STASSID "your-ssid"
// #define STAPSK "your-password"
// // #endif

// const char* ssid = STASSID;
// const char* password = STAPSK;

X509List cert(cert_DigiCert_Global_Root_CA);

void setup() {
 delay(5000);
    Serial.begin(115200);
    delay(1000);
     Ethernet.init(eth_cs);
  Ethernet.begin(mac, "AXTCP101");
  // put your setup code here, to run once:
    Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  // Set time via NTP, as required for x.509 validation
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  // while (now < 8 * 3600 * 2) {
  //   delay(500);
  //   Serial.print(".");
  //   now = time(nullptr);
  // }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));

  // Use WiFiClientSecure class to create TLS connection
  WiFiClient client;
    // client.setInsecure();
  Serial.print("Connecting to ");
  Serial.println(github_host);

  // Serial.printf("Using certificate: %s\n", cert_DigiCert_Global_Root_CA);
  // client.setTrustAnchors(&cert);

  if (!client.connect(IPAddress(10,13,100,141),5000)) {
    Serial.println("Connection failed");
    // return;
  }

  String url = "/s";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + github_host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");

  Serial.println("Request sent");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successful!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("Closing connection");
}

void loop() {}
