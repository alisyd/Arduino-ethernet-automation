// #include <Ethernet.h>

#include <ArduinoHttpClient.h>

#include <Ethernet.h>
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


int s0 = 46;
int s1 = 47;
int s2 = 48;
int s3 = 49;

int SIG = A15;
int voltage_sensor = A6; 
int relays[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};
bool relay_state[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


int current_sensors[] = {A14, A13, A12, A11, A10, A9, A8, A7};


int control_pins[] = {s0, s1, s2, s3};
int mux_channel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };


uint8_t mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

EthernetClient client;
File myFile;
char server[] = "onpremise.in";

signed long next;
signed long timer;

char SERIAL_NO[] = "ACXTCP101E";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  
  // for(int i = 0; i< sizeof(fmtStr)/8;i++) Serial.print(fmtStr[i]);
  // pinMode(ledPin9, OUTPUT);
  pinMode(sd_cs, OUTPUT);
  pinMode(eth_cs, OUTPUT);

  for(int i=0; i < 24; i++){
    pinMode(relays[0], OUTPUT);
  }
  //declare current sensors pins for input
  for(int i = 0; i < 8; i++){
    pinMode(current_sensors[i], INPUT);
  }
//mux control pins
  for(int i = 0; i < 4; i++){
    pinMode(control_pins[i], OUTPUT);
  }
  
  pinMode(SIG, INPUT);
  pinMode(voltage_sensor, INPUT);
  pinMode(eth_cs, OUTPUT);

  // Serial.write(fetchCV());

  // pinMode(relay7, OUTPUT);

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
  Ethernet.begin(mac);
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

  Serial.println(next);
  Serial.println(counter);
 
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
              // Serial.println("inside ifinity");
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
              Serial.println(newBuff);
              if (strncmp(newBuff, "relay", 5)==0){
                char relay_no_char[3];
                int relay_no;
                strncpy(relay_no_char, newBuff + strlen(newBuff)-2, 2 );
                relay_no_char[2] = '\0';
                relay_no = atoi(relay_no_char);

                if (strncmp(newBuff + 5, "On",2) == 0) {
                  Serial.print("Recieved  ON ");
                  Serial.print(relay_no);
                  digitalWrite(relays[relay_no - 1], HIGH);
                  
                }
                else if(strncmp(newBuff +5, "Off", 3) == 0){
                  Serial.print("Recieved OFF");
                  digitalWrite(relays[relay_no - 1], LOW);
                }
                client.write("ACKE", 6);
                
                goto close;
              }
              
              
              
              
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

              if (strcmp(newBuff, "fetchCV") == 0) {
                Serial.println("Recieved Current Voltage fetch");
                char * formattedCV = fetchCV();
                Serial.println("outside of fetch cv function");
                Serial.println(formattedCV);
                Serial.println(sizeof(formattedCV));
                client.write(formattedCV, strlen(formattedCV));
              }
              // if (strcmp(newBuff,"relayOn01" )== 0){
              //   Serial.println("Recieved ON Command, sending the ACK");
              //   digitalWrite(relay1, LOW);
              //   r1_state=1;
              //   strcpy(ack ,"ACKR1S");
              //   client.write(ack, 6);
              //   goto close;
              // }
       
              

              
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
  delay(2000);

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
for(int i=0; i <= 50; i++){
  float sensorValue = analogRead(pin);
  float current =(2500-(sensorValue/1023)*5000.0)/100;
  sumSqr+=current*current;
  delay(3);
}
meanSqr = sumSqr/50;
// currentRMS = sqrt(meanSqr);
return 0.344;
}
float measureVoltage(uint8_t pin){
  
ZMPT101B voltageSensor(pin, 50.0);

voltageSensor.setSensitivity(SENSITIVITY_1);
  // return voltageSensor.getRmsVoltage();
  return 220.00;

}
 


  
char* fetchCV (){
  // static char cvb[1000];
  char* cv_array[25];

  // Serial.println("inside fetch cv");
  // long start_time = millis();
  // long end_time;
  // Serial.print("Started at: ");
  // Serial.println(start_time/1000);
  for( int i = 0; i < 8; i++){
    // start_time = millis();
    cv_array[i] = ftostr(measureCurrent(current_sensors[i]));
  
  }

 for(int channel = 0; channel < 16; channel++){
   // select channel 
  //  Serial.println("Fetching from muxed current sensors");
    for(int i = 0; i < 4; i++){
      digitalWrite(control_pins[i], mux_channel[channel][i]);
    }
    cv_array[channel+8] = ftostr(measureCurrent(SIG));
  }
  cv_array[24] = ftostr(measureVoltage(voltage_sensor));

// Serial.write()
  int fmt_cvst_buff_size = 0;
  for (int i = 0; i < 25; i++) {
    Serial.println(cv_array[i]);
    fmt_cvst_buff_size += snprintf(NULL, 0, "%s", cv_array[i]);
  }

  // Add space for separators (e.g., commas) and a null terminator
  fmt_cvst_buff_size+= 27;

  for(int i = 0; i < 24; i++){
    fmt_cvst_buff_size += snprintf(NULL, 0, "%d", relay_state[i]);
  }


  // Allocate a buffer for the formatted string
  char* fmt_cvst_buff = new char[fmt_cvst_buff_size];

  // Use snprintf to format the array into the string
  int offset = 0;
  
  for (int i = 0; i < 25; i++) {
    int charsWritten = snprintf( fmt_cvst_buff + offset, fmt_cvst_buff_size - offset, "%s", cv_array[i]);
    offset += charsWritten;
    if (i < 24) {
      // Add a separator (e.g., comma) between elements
      snprintf(fmt_cvst_buff + offset, fmt_cvst_buff_size - offset, ":");
      ++offset;
    }
    if (i == 24){
      snprintf(fmt_cvst_buff+offset, fmt_cvst_buff_size - offset, ":");
      ++offset;
    }
  }

  int chars_written;
  for (int i = 0; i < 24; i++) {
    chars_written = snprintf( fmt_cvst_buff + offset, fmt_cvst_buff_size - offset, "%d", relay_state[i]);
    offset += chars_written;
  
    
  }
  snprintf(fmt_cvst_buff+offset, fmt_cvst_buff_size - offset, "%c", 'E');


  // Serial.write(fmt_cvst_buff);



  // float V = measureVoltage(A0);
 
  // static char cvb[100];
  // int len = snprintf(cvb, sizeof(cvb), "%s:%s:%s:%s:%s:%s:%s:%s:%d%d%d%d%d%d%dE",ftostr(c1),ftostr(c2),ftostr(c3),ftostr(c4),ftostr(c5),ftostr(c6),ftostr(c7),ftostr(V),r1_state,r2_state,r3_state,r4_state, r5_state, r6_state, r7_state);
  // Serial.println(len);
  // Serial.write(cvb);
  // char* cvbCopy = strdup(cvb);
    char *cvcopy = strdup(fmt_cvst_buff);
  return cvcopy;

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
