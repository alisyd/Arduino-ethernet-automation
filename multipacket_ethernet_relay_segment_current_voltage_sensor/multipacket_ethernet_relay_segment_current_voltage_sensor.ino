#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <EtherCard.h>
#define TCP_FLAGS_FIN_V 1 //as declared in net.h
#define TCP_FLAGS_ACK_V 0x10 //as declared in net.h
static byte myip[] = { 192,168,0,66 };
static byte gwip[] = { 192,168,0,250 };
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x39 };
#include <ZMPT101B.h>
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

byte Ethernet::buffer[900]; // tcp ip send and receive buffer
int ledPin8 = 8;
int ledPin9 = 9;
int ledPin7 = 7;
int ledPin6 = 6;
int ledPin5 = 5;
int ledPin4 = 4;
int ledPin3 = 3;
int ledPin2 = 2;


const char pageSeg1[] PROGMEM =
"HTTP/1.0 200 Ok\r\n"
"Content-Type: text/html\r\n"
"\r\n"
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>Sensor Data Page</title>"
;
const char pageSeg2[] PROGMEM =
"<style>"
"body {"
"font-family: Arial, sans-serif;"
"display:flex;"
"gap:20px;"
"flex-wrap:wrap;"
"margin: 0;"
    "padding: 20px;"
    "background-color: #f4f4f4;"
  "}"
  ".container {"
    "background-color: white;"
    "border-radius: 10px;"
    "padding: 20px;"
    "margin-top: 20px;"
    "box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);"
  "}"
;
const char pageSeg3[] PROGMEM =
  ".sensor-box {"
    "border: 1px solid #ccc;"
    "padding: 10px;"
    "border-radius: 5px;"
    "margin-bottom: 20px;"
  "}"
  ".toggle-button {"
    "display: inline-block;"
    "width: 60px;"
    "height: 30px;"
    "background-color: #ccc;"
    "border-radius: 15px;"
    "position: relative;"
    "cursor: pointer;"
    "transition: background-color 0.3s;"
  "}"
;
const char pageSeg4[] PROGMEM =
  ".toggle-button:before {"
    "content: '';"
    "position: absolute;"
    "width: 26px;"
    "height: 26px;"
    "background-color: white;"
    "border-radius: 50%;"
    "top: 2px;"
    "left: 2px;"
    "transition: 0.3s;"
  "}"
  "input[type=\"checkbox\"] {"
    "display: none;"
  "}"
;
const char pageSeg5[] PROGMEM =
  "input[type=\"checkbox\"]:checked + .toggle-button {"
    "background-color: #6ac259;"
  "}"
  "input[type=\"checkbox\"]:checked + .toggle-button:before {"
    "transform: translateX(30px);"
  "}"
  ".info-button {"
    "background-color: #3498db;"
    "color: white;"
    "border: none;"
    "border-radius: 5px;"
    "padding: 5px 10px;"
    "cursor: pointer;"
  "}"
;
const char pageSeg6[] PROGMEM =
  ".info-text {"
    "display: none;"
    "margin-top: 10px;"
    "padding: 10px;"
    "background-color: #f9f9f9;"
    "border-radius: 5px;"
  "}"
"</style>"
"</head>"
;
const char pageSeg7[] PROGMEM =
"<body>"
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle1\">"
    "<input type=\"checkbox\" id=\"sensorToggle1\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;
const char pageSeg8[] PROGMEM = 
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle2\">"
    "<input type=\"checkbox\" id=\"sensorToggle2\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;
const char pageSeg9[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle3\">"
    "<input type=\"checkbox\" id=\"sensorToggle3\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg10[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle4\">"
    "<input type=\"checkbox\" id=\"sensorToggle4\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg11[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle5\">"
    "<input type=\"checkbox\" id=\"sensorToggle5\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg12[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle6\">"
    "<input type=\"checkbox\" id=\"sensorToggle6\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg13[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle7\">"
    "<input type=\"checkbox\" id=\"sensorToggle7\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg14[] PROGMEM =
"<div class=\"container\">"
    "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
    "</div>"
    "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle8\">"
    "<input type=\"checkbox\" id=\"sensorToggle8\" />"
    "<div class=\"toggle-button\"></div>"
    "</label>"
    "</div>"
    "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
    "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
    "</div>"
    "</div>"
;

const char pageSeg15[] PROGMEM =
"<script>"
  "const voltageElement = document.getElementById('voltage');"
  "const currentElement = document.getElementById('current');"
  "const sensorToggle = document.getElementById('sensorToggle');"
  "const infoBtn = document.getElementById('infoBtn');"
  "const infoText = document.getElementById('infoText');"
  "const relays = document.getElementsByTagName('input');"
  "for (let i = 0; i < relays.length; i++) {"
        "console.log(relays[i]);"
        "relays[i].addEventListener('change', (event) => {"
;
const char pageSeg16[] PROGMEM =
    "if (event.target.checked) {"
      "const voltage = Math.random() * 5;"
      "const current = Math.random() * 2;"
      "voltageElement.textContent = voltage.toFixed(2) + ' V';"
      "currentElement.textContent = current.toFixed(2) + ' A';"
      "const url = 'http://10.13.100.143/?RELAY'+(i+1)+'=ON';"
      "fetch(url)"
            ".then((response) => {"
             " if (!response.ok) {"
                "throw new Error("
                  "`Network response was not ok: ${response.status}`"
               " );"
              "}"
             " return response.json();"
           "})"
            ".then((data) => {"
              "console.log(\"Data received:\", data);"
           " })"
           ".catch((error) => {"
              "console.error(\"Error:\", error);"
           " });"
;
const char pageSeg17[] PROGMEM =
"} else {"
      "voltageElement.textContent = '0 V';"
      "currentElement.textContent = '0 A';"
      "const url = 'http://10.13.100.143/?RELAY'+(i+1)+'=OFF';"
      "fetch(url)"
            ".then((response) => {"
             " if (!response.ok) {"
                "throw new Error("
                  "`Network response was not ok: ${response.status}`"
               " );"
              "}"
             " return response.json();"
           "})"
            ".then((data) => {"
              "console.log(\"Data received:\", data);"
           " })"
           ".catch((error) => {"
              "console.error(\"Error:\", error);"
           " });"
    "}"
  "})"
  "};"
  "infoBtn.addEventListener('click', () => {"
    "infoText.style.display = 'block';"
  "});"
"</script>"
"</body>"
"</html>"
;
 const char okheader[] PROGMEM =  
      "HTTP/1.0 200 OK\r\n"
       "Content-Type: application/json\r\n"
       "Connection: close\r\n"
       "\r\n"
       ;
char strBuf[300] ;
BufferFiller bfill;
Stash stash;
void setup(){
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  Serial.begin(9600);
  // voltageSensor.setSensitivity(SENSITIVITY);
  ether.begin(sizeof Ethernet::buffer, mymac , SS);
  Serial.println("starting to check for ethernet controller\n");
if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
Serial.println( "Failed to access Ethernet controller\n");
Serial.println("Setting up DHCP");
ether.dhcpSetup();
ether.printIp("IP: ", ether.myip);
ether.printIp("GW: ", ether.gwip);
ether.printIp("DNS: ", ether.dnsip);
}

void loop(){
    word pos = ether.packetLoop(ether.packetReceive());
  String securityToken = "hello123";
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY8=OFFhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin9, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY8=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin9, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY7=OFFhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin8, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY7=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin8, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY6=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin7, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY6=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin7, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY5=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin6, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY5=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin6, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY4=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin5, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY4=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin5, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY3=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin4, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY3=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin4, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY2=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin3, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY2=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin3, LOW);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY1=OFFhello123") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin2, HIGH);
}
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY1=ONhello123") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin2, LOW);
}
// if (pos) {
//         char* data = (char *) Ethernet::buffer + pos;
//         if (strncmp("GET /?currentVoltage1", data, 21) == 0) {
if(strstr((char *)Ethernet::buffer + pos, "GET /?cv=1hello123") != 0) {
Serial.println("printing the current voltage");
float current = measureCurrent(A0);
float voltage = measureVoltage(A1);
Serial.print("Current:");
Serial.println(current);
Serial.print("Voltage:");
Serial.println(voltage);
//const char jsonPayload[] PROGMEM = "{'current':"+current+",'voltage':"+voltage+" }";
DynamicJsonDocument doc(100);
doc["current"] = current;
doc["voltage"] = voltage;
String jsonString PROGMEM;
serializeJson(doc, jsonString);

// byte sd = stash.create();
// stash.print("{'current':");
// stash.print(current);
// stash.print(",'voltage:'");
// stash.print(voltage);
// stash.print("}");
// stash.save();
// int stash_size = stash.size();
// byte session;
// Stash::prepare(PSTR("HTTP/1.0 200 O\r\n"
//     "Content-Type: application/json \r\n"
//     "Content-Length: $D \r\n"
//     "\r\n"
//     "$H"),
//   stash_size, sd);
//   session = ether.tcpSend();
//   ether.tcpReply(session);

   //serializeJsonPretty(doc,jsonString);
//  const char okheader[] PROGMEM =  
//       "HTTP/1.0 200 OK\r\n"
//        "Content-Type: text/html\r\n"
//        "Connection: close\r\n"
//        "\r\n"
//        "hello";
//"{'current':0.2A, 'voltage':230}</html>"

// "HTTP/1.0 200 Ok\r\n"
// "Content-Type: appLication/json\r\n"
// "Retry-After: 600\r\n"
// "\r\n"

// "GET /?currentVoltage1 HTTP/1.1\r\n"
// "Host: 10.13.100.143/\r\n"
// "Content-Type: application/json\r\n"
// ;
// char strBuf[300] PROGMEM;
jsonString.toCharArray(strBuf,jsonString.length()+1);
Serial.println(strBuf);
 ether.httpServerReply(jsonResponse());



//   jsonReply =  strcat(jsonReply,jsonString);
  //  Serial.println(jsonString);
  //  Serial.println(strBuf); // send ack to the request
  // ether.httpServerReplyAck();
  // memcpy_P(ether.tcpOffset(), okheader, sizeof okheader);
  // ether.httpServerReply_with_flags(sizeof okheader - 1,TCP_FLAGS_ACK_V);

  // //memcpy_P(ether.tcpOffset(),strBuf , sizeof strBuf); // send first packet and not send the terminate flag
  
  // ether.httpServerReply_with_flags(sizeof  strBuf- 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V);
  //  }
        
}




    // check if valid tcp data is received
    if (pos) {
        char* data = (char *) Ethernet::buffer + pos;
        if (strncmp("GET / ", data, 6) == 0) {
            ether.httpServerReplyAck(); // send ack to the request
            memcpy_P(ether.tcpOffset(), pageSeg1, sizeof pageSeg1); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg1 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg2, sizeof pageSeg2); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg2 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg3, sizeof pageSeg3); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg3 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg4, sizeof pageSeg4); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg4 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg5, sizeof pageSeg5); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg5 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg6, sizeof pageSeg6); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg6 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg7, sizeof pageSeg7); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg7 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg8, sizeof pageSeg8); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg8 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg9, sizeof pageSeg9); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg9 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg10, sizeof pageSeg10); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg10 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg11, sizeof pageSeg11); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg11 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg12, sizeof pageSeg12); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg12 - 1,TCP_FLAGS_ACK_V);
            memcpy_P(ether.tcpOffset(), pageSeg13, sizeof pageSeg13); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg13 - 1,TCP_FLAGS_ACK_V);
             memcpy_P(ether.tcpOffset(), pageSeg14, sizeof pageSeg14); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg14 - 1,TCP_FLAGS_ACK_V);
             memcpy_P(ether.tcpOffset(), pageSeg15, sizeof pageSeg15); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg15 - 1,TCP_FLAGS_ACK_V);
             memcpy_P(ether.tcpOffset(), pageSeg16, sizeof pageSeg16); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg16 - 1,TCP_FLAGS_ACK_V);
             memcpy_P(ether.tcpOffset(), pageSeg17, sizeof pageSeg17); // send first packet and not send the terminate flag
            ether.httpServerReply_with_flags(sizeof pageSeg17 - 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V); }
        else
        {
            ether.httpServerReplyAck(); // send ack to the request
            memcpy_P(ether.tcpOffset(), pageSeg1, sizeof pageSeg1);//only the first part will sended
            ether.httpServerReply_with_flags(sizeof pageSeg1 - 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V);
        }
  }
}

static word jsonResponse(){
  bfill = ether.tcpOffset();
  float current = measureCurrent(A0);
float voltage = measureVoltage(A1);
Serial.print("Current:");
Serial.println(current);
Serial.print("Voltage:");
Serial.println(voltage);
//const char jsonPayload[] PROGMEM = "{'current':"+current+",'voltage':"+voltage+" }";
DynamicJsonDocument doc(100);
doc["current"] = current;
doc["voltage"] = voltage;
  bfill.emit_p(PSTR(
       "HTTP/1.0 200 OK\r\n"
       "Content-Type: application/json\r\n"
       "Connection: close\r\n"
       "Access-Control-Allow-Origin: *\r\n"
       "\r\n"));
  serializeJson(doc, bfill);
  return bfill.position();
}


// float measureCurrent(uint8_t pin){
//   float  sumSqr=0.0, meanSqr=0.0, currentRMS=0.0;
// for(int i=0; i <= 200; i++){
//   float sensorValue = analogRead(pin);
//   float current =(2500-(sensorValue/1023)*5000.0)/185;
//   sumSqr+=current*current;
//   delay(3);
// }
// meanSqr = sumSqr/200;
// currentRMS = sqrt(meanSqr);
// return currentRMS;
// }
// float measureVoltage(uint8_t pin){
  
// ZMPT101B voltageSensor(pin, 50.0);

// voltageSensor.setSensitivity(SENSITIVITY_1);
//   return voltageSensor.getRmsVoltage();

// }

