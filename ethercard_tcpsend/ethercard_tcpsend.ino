#include <EtherCard.h>

// MAC address for your Arduino Ethernet module
byte mac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

uint8_t* ip[]= {10,13,100,141};  // Replace with the IP address or hostname of the remote server
int serverPort = 50000;         // Replace with the port number of the remote server

byte Ethernet::buffer[700];

static uint32_t timer;

void setup() {
  Serial.begin(9600);
  
  if (ether.begin(sizeof Ethernet::buffer, mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while (true);
  }
  
  ether.dhcpSetup();
  ether.printIp("My IP: ", ether.myip);
}

void loop() {
  ether.packetLoop(ether.packetReceive());

  if (millis() - timer > 5000) {
    timer = millis();

    Serial.println("Connecting to server...");
    
    if (ether.clientTcpReq(ip, serverPort)) {
      Serial.println("Connected to server!");

      // Send data to the server
      //ether.clientPut("Hello, server!");

      // You can also receive data from the server
      while (ether.clientAvailable()) {
        char c = ether.clientGet();
        Serial.print(c);
      }

      // Close the connection
      ether.clientDisconnect();
    } else {
      Serial.println("Connection failed.");
    }
  }

  // Other tasks or code can go here
}
