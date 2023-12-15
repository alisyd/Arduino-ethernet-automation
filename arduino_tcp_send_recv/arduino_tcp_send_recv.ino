/*
 * UIPEthernet TcpClient example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *      -----------------
 *
 * This TcpClient example gets its local ip-address via dhcp and sets
 * up a tcp socket-connection to 192.168.0.1 port 5000 every 5 Seconds.
 * After sending a message it waits for a response. After receiving the
 * response the client disconnects and tries to reconnect after 5 seconds.
 *
 * Copyright (C) 2013 by Norbert Truchsess <norbert.truchsess@t-online.de>
 */

#include <UIPEthernet.h>
#include <SD.h>
EthernetClient client;
signed long next;
int ledPin9 = 9;
char SERIAL_NO[] = "AXTCP101";

void setup() {
  // int ledPin9 = 9;
  Serial.begin(9600);
  pinMode(ledPin9, OUTPUT);
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

  next = 0;
}

void loop() {
  if (((signed long)(millis() - next)) > 0) {
    next = millis() + 5000;
    Serial.println("Client connect");
    // replace hostname with name of machine running tcpserver.pl
    //      if (client.connect("server.local",5000))
    if (client.connect(IPAddress(10, 13, 100, 141), 50000)) {
      Serial.println("Client connected");
      // client.println("DATA from Client");
      while (client.available() == 0) {

        if (next - millis() < 0)
          goto close;
      }
      int size;

      while ((size = client.available()) > 0) {
        // // char buffer[size];
        // uint8_t* msg = (uint8_t*)malloc(size);
        // // char
        // // msg = client.read()
        // size = client.read(msg, size);

        // // for (i = 0; i<size; i++){
        // // // //   buffer[i] = *(msg)
        // char buffer_poll[size];
        // Serial.println(size);
        // size = client.read(buffer_poll, size);
        // // }
        // Serial.println(size);
        char poll_buff[size];
        Serial.println(size);
        size = client.read(poll_buff, size);
        client.flush();
        Serial.write(poll_buff, size);

        client.write(SERIAL_NO, sizeof(SERIAL_NO));
        client.flush();
        // size = client.available();
        size = 10;
        // delay(2000);
        char buffer[size];
        Serial.println(size);
        int counter = 0;
        while (true) {
          size = client.read(buffer, 15);
          if (size > 0) {
            break;
          }
          // if (counter == 10){
          //   break;

          // }
        }
        Serial.write(buffer, size);
        Serial.println(size);
        char newBuff[size];

        for (int i = 0; i < size; i++) {
          if (buffer[i] != 'E') {
            newBuff[i] = buffer[i];
            Serial.print(newBuff[i]);
          } else {
            newBuff[i] = 0;
            break;
          }
        }

        Serial.print('\n');
        String relayCommand = "relayOn01";
        int flag = 0;
        // for (int i = 0; i <sizeof(newBuff); i++){
        //   // Serial.println("inside of the loop");
        //     if (newBuff[i] != relayCommand[i]){
        //       Serial.println("Cannot parse the command");
        //       flag= 0;
        //     }
        // }
        Serial.println(strcmp(newBuff, "relayOn01"));
        // if (strcmp(newBuff, "relayOn01")==0){
        //   flag = 1;
        // }
        char ack[3] = "ACK";
        if (strcmp(newBuff, "relayOn01") == 0) {
          Serial.println("Recieved ON Command, sending the ACK");
          digitalWrite(ledPin9, LOW);

          client.write(ack, 3);
        }
        if (strcmp(newBuff, "relayOff01") == 0) {
          Serial.println("Recieved OFF command, sending the ACK");
          digitalWrite(ledPin9, HIGH);
          // char ack[3] = "ACK";
          client.write(ack, 3);
        }
        // Serial.println(newBuff);
        // Serial.println(buffer);

        // Serial.write(msg,size);
        //  free(msg);
        // Serial.println(replyBuffer);
      }
      delay(2000);
close:
      //disconnect client
      Serial.println("Client disconnect");
      // Serial.println("Turning of the relay");
      client.stop();


    } else
      Serial.println("Client connect failed");
  }
}
