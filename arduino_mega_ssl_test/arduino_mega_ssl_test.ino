
#include <Arduino.h>

#include <UIPEthernet.h>

#include <ESP_SSLClient.h>


ESP_SSLClient ssl_client;
EthernetClient basic_client;
int eth_cs = 5;
int next;

uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
char SERIAL_NO[] = "AXTCP101";

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
  

    // Set the receive and transmit buffers size in bytes for memory allocation (512 to 16384).
    ssl_client.setBufferSizes(16384/* rx */, 512 /* tx */);
    ssl_client.setDebugLevel(1);

    // Assign the basic client
    // Due to the basic_client pointer is assigned, to avoid dangling poin````````````ter, basic_client should be existed
    // as long as it was used by ssl_client for transportation.
    ssl_client.setClient(&basic_client);
    ssl_client.setInsecure();
    next = 0;


}

void loop() {
  if (((signed long)(millis() - next)) > 0)
    {
      next = millis() + 5000;
      Serial.println("Client connect");
      // replace hostname with name of machine running tcpserver.pl
//      if (client.connect("server.local",5000))
      if (ssl_client.connect("www.google.com",443, 20000))
        {
          Serial.println("Client connected");
          Serial.println(" ok");
        Serial.println("Send GET request...");
         ssl_client.print("GET / HTTP/1.1\n");
        ssl_client.print("Host: secure.onpremise.in\n");
        ssl_client.print("Connection: keep-alive\n");
        ssl_client.print("\n");
       
          // client.println("DATA from Client");
          while(ssl_client.available()==0)
            {
              // Serial.println(next-millis());
              if (millis() > next)
                goto close;
            }
          int size;
          int count;
          while( (size = ssl_client.available())>0)
            {
              // Serial.println("inside of the client loop");
              Serial.print((char)ssl_client.read());
              count+=1;
           


            }
            Serial.println();
            Serial.println(count);
            delay(2000);

close:
          //disconnect client
          Serial.println("Client disconnect");
          // Serial.println("Turning of the relay");
          ssl_client.stop();


        }
      else
        Serial.println("Client connect failed");
    }
}

