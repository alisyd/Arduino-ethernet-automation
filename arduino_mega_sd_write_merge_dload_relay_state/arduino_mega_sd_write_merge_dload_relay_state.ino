#include <ArduinoHttpClient.h>

#include <UIPEthernet.h>
#include <SPI.h>
#include <SD.h>
#include <ZMPT101B.h>
#include <stdlib.h>
#include <avr/wdt.h>
// #include <MemoryFree.h>
#define SENSITIVITY_1 470.75000f
// #define LED_BUILTIN 25
// #include <cstring> // Include the necessary header for strdup

const char* BIN_FILENAME = "FIRMWARE.BIN"; // sd card firmware file location

// int ResetPin = 4;
// int EthCS = 6;
// int EthTrig = 8;
// int relayTrig =7;
// bool r1_state = 1;
// bool r2_state = 2;
// bool r3_state = 

int sd_cs = 10;
int eth_cs = 4;
int relay1 = 16;
int relay2 = 17;
int relay3 = 18;
int relay4 = 19;
int relay6 = 20;
int relay5 = 21;
int relay7 = 22;


int counter = 0;
bool r1_state= 1;
bool r2_state = 1;
bool r3_state = 1;
bool r4_state = 1;
bool r5_state = 1;
bool r6_state = 1;
bool r7_state = 1;

  uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

EthernetClient client;
File myFile;
char server[] = "onpremise.in";

signed long next;
signed long timer;

char SERIAL_NO[] = "AXTCP101";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial.write(fetchCV());
  
  // for(int i = 0; i< sizeof(fmtStr)/8;i++) Serial.print(fmtStr[i]);
  // pinMode(ledPin9, OUTPUT);
  pinMode(sd_cs, OUTPUT);
  pinMode(eth_cs, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);

  // pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(progTrig, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
  // digitalWrite(progTrig, HIGH);
  delay(2000);
  Serial.print("Initializing SD card...");
sd_sel();
  if (!SD.begin(sd_cs)) {
    Serial.println("initialization failed!");
    // while (1);
  }
  Serial.println("initialization done.");
 

  eth_sel();
  Serial.println("Enabled Ethernet Module");
   Serial.println("Selecting Ethernet");
  // digitalWrite(ETH_EN, LOW);
  Ethernet.init(eth_cs);
  Ethernet.begin(mac, "AXTCP101");
  // Ethernet.maintain();

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
  // Ethernet.maintain();
  // Serial.println(Ethernet.localIP());
  // next = 0;
  // ctrloop +=1;
  Ethernet.maintain();
  counter +=1;
  // if (counter%150==0){
  //     Ethernet.init(eth_cs);
  // Ethernet.begin(mac, "AXTCP101");
  // // Ethernet.maintain();

  // Serial.print("localIP: ");
  // Serial.println(Ethernet.localIP());
  // Serial.print("subnetMask: ");
  // Serial.println(Ethernet.subnetMask());
  // Serial.print("gatewayIP: ");
  // Serial.println(Ethernet.gatewayIP());
  // Serial.print("dnsServerIP: ");
  // Serial.println(Ethernet.dnsServerIP());
  // }
  Serial.println(next);
  Serial.println(counter);
  // int freeMem = memoryFree();
  // Serial.println(freeMem);
  // char* fmtStr = fetchCV();
  // Serial.println(fmtStr);
  // free(fmtStr);
  // char bf[10];
  // float test = 0.445;
  // char* tet = ftostr(test);
  // Serial.println(tet);
  digitalWrite(LED_BUILTIN, LOW);
  if (((signed long)(millis() - next)) > 0)
    {
    next = millis() + 5000;
      Serial.println("Client connect");
  // digitalWrite(LED_BUILTIN, HIGH);

      // replace hostname with name of machine running tcpserver.pl
     if (client.connect(IPAddress(10, 13, 100, 133),4040))
      // if (client.connect(IPAddress(15,207,232,168),50000))
        {
  // digitalWrite(LED_BUILTIN, HIGH);
  //         delay(100);
  // digitalWrite(LED_BUILTIN, LOW);
  //         delay(100);
  // digitalWrite(LED_BUILTIN, HIGH);

          Serial.println("Client connected");
          // client.println("DATA from Client");
          while(client.available()==0)
            {
              Serial.println(next-(signed long)millis());
              // timer = next - millis()
              // if(()millis() - next == 200){
                // Ethernet.maintain();
              // }
              if (next <  millis()){
                goto close;
              }
            }
          int size;
           
          while( (size = client.available())>0)
            {
    
              char poll_buff[size];
              Serial.println(size);
              size = client.read(poll_buff, size);
              // client.flush();
              Serial.write(poll_buff,size);

              client.write(SERIAL_NO, sizeof(SERIAL_NO));
              // client.flush();
              // size = client.available();
              size = 10;
              // delay(2000);
              char buffer[size];
              Serial.println(size);
              int counter = 0;
              long timer = millis() + 2000;
              
              while(true){

              size = client.read(buffer, 15);
              if (size > 0){
                break;
              }
              else if (timer < millis()){
                goto close;
              }
              Serial.println("inside ifinity");
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
    
              Serial.println(strcmp(newBuff, "DLOADFWSD"));
              // if (strcmp(newBuff, "relayOn01")==0){
              //   flag = 1;
              // }
              char ack[7];
              if (strcmp(newBuff,"DLOADFWSD" )== 0){
                Serial.println("Recieved SD download flag, downloading firmware on sd card");
                strcpy(ack, "ACKFWD");
                client.write(ack, 6);
                Serial.println("Socket closed, downloading firmware");
                client.stop();
                delay(2000);
                handleSketchDownload();
                Serial.println("Handle donwload executed");
                goto close;
              }
              if (strcmp(newBuff,"FLAGSDBOOT" )== 0){
                Serial.println("Recieved the sd boot flag, setting sd boot flag");
                // digitalWrite(ledPin9, LOW);
                strcpy(ack, "ACKSBT");
                client.write(ack, 7);
                client.stop();
                Serial.println("Triggering sd boot, please restart device after a few seconds");
                setBootResetFlag();
              }
              if (strcmp(newBuff,"relayOn01" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay1, LOW);
                r1_state=1;
                strcpy(ack ,"ACKR1S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff01")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay1, HIGH);
                r1_state=0;
                // char ack[3] = "ACK";
                strcpy(ack ,"ACKR1R");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOn02" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay2, LOW);
                r2_state = 1;
                strcpy(ack ,"ACKR2S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff02")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay2, HIGH);
                r2_state = 0;
                // char ack[3] = "ACK";
                strcpy(ack ,"ACKR2R");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOn03" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay3, LOW);
                r3_state = 1;
                strcpy(ack ,"ACKR3S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff03")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay3, HIGH);
                r3_state = 0;
                // char ack[3] = "ACK";
                strcpy(ack ,"ACKR3R");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOn04" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay4, LOW);
                r4_state = 1;
                strcpy(ack,"ACKR4S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff04")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay4, HIGH);
                r4_state = 0;
                // char ack[3] = "ACK";
                // goto close;
                strcpy(ack, "ACKR4R");
                client.write(ack, 6);
                goto close;
              }
               if (strcmp(newBuff,"relayOn05" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay5, LOW);
                r5_state = 1;
                strcpy(ack,"ACKR5S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff05")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay5, HIGH);
                r5_state = 0;
                // char ack[3] = "ACK";
                // goto close;
                strcpy(ack, "ACKR5R");
                client.write(ack, 6);
                goto close;
              }
               if (strcmp(newBuff,"relayOn06" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay6, LOW);
                r6_state = 1;
                strcpy(ack,"ACKR6S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff06")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay6, HIGH);
                r6_state = 0;
                // char ack[3] = "ACK";
                // goto close;
                strcpy(ack, "ACKR6R");
                client.write(ack, 6);
                goto close;
              }
               if (strcmp(newBuff,"relayOn07" )== 0){
                Serial.println("Recieved ON Command, sending the ACK");
                digitalWrite(relay7, LOW);
                r7_state = 1;
                strcpy(ack,"ACKR7S");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"relayOff07")==0){
                Serial.println("Recieved OFF command, sending the ACK");
                digitalWrite(relay7, HIGH);
                r7_state = 0;
                // char ack[3] = "ACK";
                // goto close;
                strcpy(ack, "ACKR7R");
                client.write(ack, 6);
                goto close;
              }
              if (strcmp(newBuff,"fetchCV")==0){
                Serial.println("Recieved Current Voltage Read, sending data");

                char * formattedCV = fetchCV();
                client.write(formattedCV,100);
                free(formattedCV);
                goto close;

                // client.write(ack,3);
              }
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
                float voltage = 230.00;
                // float voltage = measureVoltage(A0);

                float current = 0.445;
                // float current = measureCurrent(A2);

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
                float voltage = 230.00;
                // float voltage = measureVoltage(A0);

                float current = 0.445;
                // float current = measureCurrent(A3);

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
                float voltage = 230.00;
                // float voltage = measureVoltage(A0);

                float current = 0.445;
                // float current = measureCurrent(A4);

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
  digitalWrite(LED_BUILTIN, HIGH);
  // delay(100);
  Ethernet.maintain();

}

bool handleSketchDownload() {

  const char* SERVER = "onpremise.in"; // must be string for HttpClient
  const unsigned short SERVER_PORT = 5000;
  // const char* PATH = "/update-v%d.bin";
  const unsigned long CHECK_INTERVAL = 5000;

  // static unsigned long previousMillis;

  // unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis < CHECK_INTERVAL)
  //   return;
  // previousMillis = currentMillis;

  // EthernetClient client;
   EthernetClient transport;
  HttpClient client(transport, SERVER, SERVER_PORT);

  // char buff[32];
  // snprintf(buff, sizeof(buff), PATH, VERSION + 1);

  Serial.print("Check for update file ");
  // Serial.println(buff);
  eth_sel();

  client.get("/firmware/bin/latest");

  int statusCode = client.responseStatusCode();
  Serial.println(statusCode);
  Serial.print("Update status code: ");
  Serial.println(statusCode);
  if (statusCode != 200) {
    client.stop();
    return;
  }

  // long length = 45;
  Serial.println(client.contentLength());
  unsigned long length = client.contentLength();
  if (length == HttpClient::kNoContentLengthHeader) {
    client.stop();
    Serial.println("Server didn't provide Content-length header. Can't continue with update.");
    return;
  }
  Serial.print("Server returned update file of size ");
  Serial.print(length);
  Serial.println(" bytes");
  // Serial.println("Response code: "+ String(client.));
  Serial.println(client.responseBody());
  sd_sel();
  Serial.println("Checking for the File");
  if (SD.exists(BIN_FILENAME)){
  Serial.println("File exists, removing the file");
  SD.remove(BIN_FILENAME);
  }
  File file = SD.open(BIN_FILENAME, O_CREAT | O_WRITE);
  if (!file) {
    client.stop();
    Serial.println("Could not create bin file. Can't continue with update.");
    return;
  }

          
  byte b;
  while (length > 0) {
    eth_sel();
    // Serial.println("inside while");
    client.readBytes( &b, 1);
      sd_sel();
    // Serial.write(b);
    file.write(b);
    length--;
  }
  file.close();
  client.stop();
  if (length > 0) {
    SD.remove(BIN_FILENAME);
    Serial.print("Timeout downloading update file at ");
    Serial.print(length);
    Serial.println(" bytes. Can't continue with update.");
    return;
  }
  Serial.println("Update file saved. Reset.");
  Serial.flush();
}

void eth_sel(){
  digitalWrite(sd_cs, HIGH);
  digitalWrite(eth_cs, LOW);
}
void sd_sel(){
  digitalWrite(sd_cs, LOW);
  digitalWrite(eth_cs,HIGH);

}

float measureCurrent(uint8_t pin){
  float  sumSqr=0.0, meanSqr=0.0, currentRMS=0.0;
for(int i=0; i <= 200; i++){
  float sensorValue = analogRead(pin);
  float current =(2500-(sensorValue/1023)*5000.0)/100;
  sumSqr+=current*current;
  delay(3);
}
meanSqr = sumSqr/200;
currentRMS = sqrt(meanSqr);
return currentRMS;
}
float measureVoltage(uint8_t pin){
  
ZMPT101B voltageSensor(pin, 50.0);

voltageSensor.setSensitivity(SENSITIVITY_1);
  return voltageSensor.getRmsVoltage();

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
char* fetchCV (){
  // static char cvb[1000];
  float c1 = measureCurrent(A1);
  
  // dtostrf(test,4,2,);
  // snprintf(bf, 10, "%s", tst);

  // float c1 = 0.441;
  
  float c2 = measureCurrent(A2);
  // float c2 = 0.442;
  
  float c3 = measureCurrent(A3);
  // float c3 = 0.443;
  
  float c4 = measureCurrent(A4);
  float c5 = measureCurrent(A5);

  float c6 = measureCurrent(A6);

  float c7 = measureCurrent(A7);

  // float c4 = 0.445;
  
  float V = measureVoltage(A0);
  // float V = 220.00;
  // int len = snprintf(NULL, 0,"%f-%f:%f-%f:%f-%f:%f-%f",c1,V,c2,V,c3,V,c4,V); 
  static char cvb[100];
  int len = snprintf(cvb, sizeof(cvb), "%s:%s:%s:%s:%s:%s:%s:%s:%d%d%d%d%d%d%dE",ftostr(c1),ftostr(c2),ftostr(c3),ftostr(c4),ftostr(c5),ftostr(c6),ftostr(c7),ftostr(V),r1_state,r2_state,r3_state,r4_state, r5_state, r6_state, r7_state);
  Serial.println(len);
  Serial.write(cvb);
  char* cvbCopy = strdup(cvb);

  return cvbCopy;

}
char* ftostr(float num){
  char temp[20];
  dtostrf(num, 4 , 2,temp);
  char* tempCpy = strdup(temp);
  return tempCpy;
  
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
