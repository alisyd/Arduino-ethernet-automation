#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Replace with your module's MAC address
IPAddress ip(192, 168, 1, 138); // Replace with your desired IP address
EthernetClient client;

void setup() {
  pinMode(2, INPUT); // CRS pin
  pinMode(3, OUTPUT); // TXEN pin
  pinMode(4, OUTPUT); // TX1 pin

  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  if (client.connect("www.example.com", 80)) {
    client.println("GET / HTTP/1.1");
    client.println("Host: www.example.com");
    client.println("Connection: close");
    client.println();
  }
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  client.stop();
  delay(10000); // Delay before sending the next request
}
