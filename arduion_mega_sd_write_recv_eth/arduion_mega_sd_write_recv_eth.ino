#include <ArduinoHttpClient.h>

#include <UIPEthernet.h>
#include <SPI.h>
#include <SD.h>
#ifdef ARDUINO_ARCH_AVR
#include <avr/wdt.h> // for self reset
  const char* BIN_FILENAME = "FIRMWARE.BIN"; // expected by zevero avr_boot
#endif


int miso_sd = 22;
int mosi_sd = 23;
int sck_sd = 24;
int ss_sd = 25;
int sd_cs = 7;
int eth_cs = 4;
EthernetClient client;
File myFile;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(miso_sd, OUTPUT);
  pinMode(mosi_sd, OUTPUT);
  pinMode(sck_sd, OUTPUT);
  pinMode(ss_sd, OUTPUT);
  pinMode(sd_cs, OUTPUT);
  pinMode(eth_cs, OUTPUT);
  // digitalWrite(eth_cs,HIGH);
  deselect_sd();
  delay(5000);
  select_sd();
  delay(10000);
  Serial.print("Initializing SD card...");
sd_sel();
  if (!SD.begin(sd_cs)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  eth_sel();
  Serial.println("Enabled Ethernet Module");
  uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
  Serial.println("Selecting Ethernet");
  // digitalWrite(ETH_EN, LOW);
  Ethernet.init(eth_cs);
  // digitalWrite(ETH_CS, HIGH);
  Ethernet.begin(mac, "AXTCP101");

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
  Serial.println("Checking for a serial command");
  delay(5000);
  while(Serial.available() > 0){
    char command = Serial.read();
    char temp = 'r';
    Serial.println(command);
    Serial.println("Inside the while loop");
    Serial.println(command == temp);
    Serial.println(sizeof command);
    Serial.println(sizeof temp);
    if (command == 's'){
      Serial.println("Recieved command set");
      Serial.println("Selecting SD card module");
      digitalWrite(eth_cs, HIGH);
      select_sd();
      delay(5000);
      myFile = SD.open("FIRMWARE.BIN");
      if (myFile) {
      Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
    // close the file:
      myFile.close();
      } else {
    // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      }
      digitalWrite(eth_cs, LOW);

    }
    if (command == 'r'){
      Serial.println("Recieved command set");
      Serial.println("Selecting SD card module");
      deselect_sd();
      
    }
    if (command == 'd'){
  
      Serial.println("Recieved command download");
      Serial.println("Selecting SD card module");
      select_sd();
      SD.remove(BIN_FILENAME);
      handleSketchDownload();
      
    }
    

}
}

void select_sd() {
  digitalWrite(miso_sd, LOW);
  digitalWrite(mosi_sd, LOW);
  digitalWrite(sck_sd, LOW);
  digitalWrite(ss_sd, LOW);
}
void deselect_sd() {
  digitalWrite(miso_sd, HIGH);
  digitalWrite(mosi_sd, HIGH);
  digitalWrite(sck_sd, HIGH);
  digitalWrite(ss_sd, HIGH);
}
void eth_sel(){
  digitalWrite(sd_cs, HIGH);
  digitalWrite(eth_cs, LOW);
}
void sd_sel(){
  digitalWrite(sd_cs, LOW);
  digitalWrite(eth_cs,HIGH);

}


void handleSketchDownload() {

  const char* SERVER = "10.13.100.141"; // must be string for HttpClient
  const unsigned short SERVER_PORT = 5000;
  const char* PATH = "/update-v%d.bin";
  const unsigned long CHECK_INTERVAL = 5000;

  static unsigned long previousMillis;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis < CHECK_INTERVAL)
    return;
  previousMillis = currentMillis;

  // EthernetClient client;
   EthernetClient transport;
  HttpClient client(transport, SERVER, SERVER_PORT);

  char buff[32];
  // snprintf(buff, sizeof(buff), PATH, VERSION + 1);

  Serial.print("Check for update file ");
  Serial.println(buff);
  eth_sel();
  //  if (client.connect(IPAddress(10,13,100,141),5000)) {  //starts client connection, checks for connection
  //   Serial.println("connected.....");
  //   client.println("GET /firmware/bin/latest"); //download text
  //   client.println("Host: 10.13.100.141");
  //   client.println("Connection: close");  //close 1.1 persistent connection 
  //   client.println(); //end of get request
  //   // int size;
  //   // Serial.println(size = client.available());
  //   //  while( (size = client.available())>0)
  //   //         {
  //   //           Serial.println("inside of the while");
  //   //           char poll_buff[size];
  //   //           Serial.println(size);
  //   //           size = client.read(poll_buff, size);
  //   //           // client.flush();
  //   //           Serial.write(poll_buff,size);

  //   //           // client.write(SERIAL_NO, sizeof(SERIAL_NO));
  //   //           // client.flush();
  //           // }
  // }
  // else {
  //   Serial.println("connection failed"); //error message if no client connect
  // }

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
    long length = client.contentLength();
  if (length == HttpClient::kNoContentLengthHeader) {
    client.stop();
    Serial.println("Server didn't provide Content-length header. Can't continue with update.");
    return;
  }
  Serial.print("Server returned update file of size ");
  Serial.print(length);
  Serial.println(" bytes");

  File file = SD.open(BIN_FILENAME, O_CREAT | O_WRITE);
  if (!file) {
    client.stop();
    Serial.println("Could not create bin file. Can't continue with update.");
    return;
  }
              // int size;

    
          // while( (size = client.available())>0)
          //   {
          //     Serial.println("inside of the while");
          //     char poll_buff[size];
          //     Serial.println(size);
          //     size = client.read(poll_buff, size);
          //     // client.flush();
          //     Serial.write(poll_buff,size);

          //     // client.write(SERIAL_NO, sizeof(SERIAL_NO));
          //     // client.flush();
            // }
          
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