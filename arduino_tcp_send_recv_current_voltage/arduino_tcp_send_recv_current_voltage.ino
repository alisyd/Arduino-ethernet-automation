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
#include <ZMPT101B.h>
#include <stdlib.h>


#define SENSITIVITY_1 674.75000f
float measureVoltage(uint8_t pin){
  
ZMPT101B voltageSensor(pin, 50.0);

voltageSensor.setSensitivity(SENSITIVITY_1);
  return voltageSensor.getRmsVoltage();

}

float measureCurrent(uint8_t pin){
  float  sumSqr=0.0, meanSqr=0.0, currentRMS=0.0;
for(int i=0; i <= 200; i++){
  float sensorValue = analogRead(pin);
  float current =(2500-(sensorValue/1023)*5000.0)/185;
  sumSqr+=current*current;
  delay(3);
}
meanSqr = sumSqr/200;
currentRMS = sqrt(meanSqr);
return currentRMS;
}

 int countDigits(float fnum, int prec){
    int count = 0;
    int num = fnum*prec;
  while (num != 0){
    count+=1;
    num = num/10;
  }
  if (count == 3){
    count +=2;
  }
  else if (count > 3){
    count+=1;
  }
  return count;

}


char * formatCV(float current, float voltage) {
  int cSize = countDigits(current, 1000);
  int vSize = countDigits(voltage, 100);
  Serial.println(cSize);
  Serial.println(vSize);
  static char cBuff[10];
  static char vBuff[10];
  static char cvBuff[30];

  dtostrf(current, cSize, 3, cBuff);
  dtostrf(voltage, vSize, 2, vBuff);
  for (int i = 0; i < cSize; i++) {
    cvBuff[i] = cBuff[i];
  }
  cvBuff[cSize] = ':';
  for (int i = 0; i < vSize; i++) {
    cvBuff[i + cSize + 1] = vBuff[i];
  }

  cvBuff[vSize+cSize+1] = "\0";

  return cvBuff;
}

EthernetClient client;
signed long next;
int ledPin9 = 9;
char SERIAL_NO[] = "AXTCP101";
int ETHCS = 4;
int progTrig = 5;
void setup() {
  // int ledPin9 = 9;
  Serial.begin(9600);
  pinMode(ledPin9, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(progTrig, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
  digitalWrite(progTrig, HIGH);
  delay(5000);
  Ethernet.init(ETHCS);
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
  if (((signed long)(millis() - next)) > 0)
    {
      next = millis() + 5000;
      Serial.println("Client connect");
      // replace hostname with name of machine running tcpserver.pl
//      if (client.connect("server.local",5000))
      if (client.connect(IPAddress(10,13,100,141),50000))
        {
          Serial.println("Client connected");
          // client.println("DATA from Client");
          while(client.available()==0)
            {

              if (next - millis() < 0)
                goto close;
            }
          int size;
           
          while( (size = client.available())>0)
            {
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
              Serial.write(poll_buff,size);

              client.write(SERIAL_NO, sizeof(SERIAL_NO));
              client.flush();
              // size = client.available();
              size = 10;
              // delay(2000);
              char buffer[size];
              Serial.println(size);
              int counter = 0;
              while(true){
              size = client.read(buffer, 15);
              if (size > 0){
                break;
              }
              // if (counter == 10){
              //   break;
              
              // }
              }
              Serial.write(buffer,size);
              Serial.println(size);
               char newBuff[size];

              for (int i = 0; i < size ; i++){
                if (buffer[i] != 'E'){
                  newBuff[i] =buffer[i];
                  Serial.print(newBuff[i]);
                }
                else{
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
              if (strcmp(newBuff,"relayOn01" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(ledPin9, LOW);
                
                client.write(ack, 3);
              }
              if (strcmp(newBuff,"relayOff01")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(ledPin9, HIGH);
                // char ack[3] = "ACK";
                client.write(ack, 3);
              }
              Serial.println(newBuff);
              Serial.println(strcmp(newBuff, "relayCV01"));
              if (strcmp(newBuff,"relayCV01")==0){
                Serial.println("Recieved Current Voltage Read, sending data");
                float voltage = 230.00;
                // float voltage = measureVoltage(A0);

                float current = 0.445;
                // float current = measureCurrent(A1);

                char * formattedCV = formatCV(current,voltage);
                client.write(formattedCV, 30);
                // client.write(ack,3);
                Serial.print("Current: ");
                Serial.println(current);
                Serial.println("Voltage: ");
                Serial.println(voltage);
                Serial.println("Formatted Current, Voltage: ");
                Serial.println(formattedCV);
              }
              if (strcmp(newBuff,"relayCV02")==0){
                Serial.println("Recieved Current Voltage Read, sending data");
                // float voltage = 230.00;
                float voltage = measureVoltage(A0);

                // float current = 0.445;
                float current = measureCurrent(A2);

                char * formattedCV = formatCV(current,voltage);
                client.write(formattedCV, 30);
                // client.write(ack,3);
                Serial.print("Current: ");
                Serial.println(current);
                Serial.println("Voltage: ");
                Serial.println(voltage);
                Serial.println("Formatted Current, Voltage: ");
                Serial.println(formattedCV);
              }
              if (strcmp(newBuff,"relayCV03")==0){
                Serial.println("Recieved Current Voltage Read, sending data");
                // float voltage = 230.00;
                float voltage = measureVoltage(A0);

                // float current = 0.445;
                float current = measureCurrent(A3);

                char * formattedCV = formatCV(current,voltage);
                client.write(formattedCV, 30);
                // client.write(ack,3);
                Serial.print("Current: ");
                Serial.println(current);
                Serial.println("Voltage: ");
                Serial.println(voltage);
                Serial.println("Formatted Current, Voltage: ");
                Serial.println(formattedCV);
              }
              if (strcmp(newBuff,"relayCV04")==0){
                Serial.println("Recieved Current Voltage Read, sending data");
                // float voltage = 230.00;
                float voltage = measureVoltage(A0);

                // float current = 0.445;
                float current = measureCurrent(A4);

                char * formattedCV = formatCV(current,voltage);
                client.write(formattedCV, 30);
                // client.write(ack,3);
                Serial.print("Current: ");
                Serial.println(current);
                Serial.println("Voltage: ");
                Serial.println(voltage);
                Serial.println("Formatted Current, Voltage: ");
                Serial.println(formattedCV);
              }
              
            }
            delay(2000);
      
close:
          //disconnect client
          Serial.println("Client disconnect");
          // Serial.println("Turning of the relay");
          client.stop();


        }
      else
        Serial.println("Client connect failed");
    }
}


void setBootResetFlag(){
  MCUCR = (1<<IVCE);
    // Move interrupts to Boot Flash section
    MCUCR = (1<<IVSEL);

    // enable watchdog timer
    wdt_enable(WDTO_15MS);

    // block waiting for the watchdog to timeout and jump to the bootloader
    while(1);
}
