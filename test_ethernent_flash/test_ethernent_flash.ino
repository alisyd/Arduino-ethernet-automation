#include <UIPEthernet.h>
EthernetClient client;

void setup() {
  // int ledPin9 = 9;
  Serial.begin(9600);
  // pinMode(ledPin9, OUTPUT);
  uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
  Ethernet.begin(mac, "ACXTCP101");

  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop");

}
