#include <UIPEthernet.h>

static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
static byte myip[] = { 192, 168, 1, 100 };

void setup() {
  Serial.begin(9600);
  
  Ethernet.begin(mymac, myip);
}

void loop() {
  Ethernet.maintain();
  
  if (millis() > 5000) {
    Serial.println("Sending HTTP GET request");
    
    EthernetClient client;
    
    if (client.connect("www.google.com", 80)) {
      client.println("GET / HTTP/1.1");
      client.println("Host: www.google.com");
      client.println("Connection: close");
      client.println();
      
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
      }
      
      client.stop();
      delay(10000); // Wait before sending the next request
    }
  }
}
