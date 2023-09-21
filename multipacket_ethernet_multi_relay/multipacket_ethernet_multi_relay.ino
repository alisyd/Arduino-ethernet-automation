#include <EtherCard.h>
#include <avr/pgmspace.h>
#define TCP_FLAGS_FIN_V 1 //as declared in net.h
#define TCP_FLAGS_ACK_V 0x10 //as declared in net.h
static byte myip[] = { 192,168,0,66 };
static byte gwip[] = { 192,168,0,250 };
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x39 };


byte Ethernet::buffer[900]; // tcp ip send and receive buffer
int ledPin8 = 8;
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
"margin: 0;"
    "padding: 20px;"
    "background-color: #f4f4f4;"
  "}"
  ".container {"
    "background-color: white;"
    "border-radius: 10px;"
    "padding: 20px;"
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
;
const char pageSeg8[] PROGMEM =
  "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle\">"
      "<input type=\"checkbox\" id=\"sensorToggle\">"
      "<div class=\"toggle-button\"></div>"
    "</label>"
  "</div>"
;
const char pageSeg9[] PROGMEM =
  "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
  "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
  "</div>"
"</div>"
;
const char pageSeg10[] PROGMEM =
"<script>"
  "const voltageElement = document.getElementById('voltage');"
  "const currentElement = document.getElementById('current');"
  "const sensorToggle = document.getElementById('sensorToggle');"
  "const infoBtn = document.getElementById('infoBtn');"
  "const infoText = document.getElementById('infoText');"
  "sensorToggle.addEventListener('change', (event) => {"
;
const char pageSeg11[] PROGMEM =
    "if (sensorToggle.checked) {"
      "const voltage = Math.random() * 5;"
      "const current = Math.random() * 2;"
      "voltageElement.textContent = voltage.toFixed(2) + ' V';"
      "currentElement.textContent = current.toFixed(2) + ' A';"
      "const url = 'http://10.13.100.143/?RELAY=ON';"
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
const char pageSeg12[] PROGMEM =
"} else {"
      "voltageElement.textContent = '0 V';"
      "currentElement.textContent = '0 A';"
      "const url = 'http://10.13.100.143/?RELAY=OFF';"
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
  "});"
  "infoBtn.addEventListener('click', () => {"
    "infoText.style.display = 'block';"
  "});"
"</script>"
"</body>"
"</html>"
"<button><a href=\"/?RELAY=ON\" style=\"text-decoration = none;\">ON</a></button>"
"<button><a href=\"/?RELAY=OFF\" style=\"text-decoration = none;\">OFF</a></button>"
;

const char* const pageSegments[] PROGMEM = {pageSeg1, pageSeg2, pageSeg3, pageSeg4, pageSeg5, pageSeg6, pageSeg7, pageSeg8, pageSeg9, pageSeg10,pageSeg11, pageSeg12};
void setup(){
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  pinMode(ledPin8, OUTPUT);
  Serial.begin(9600);
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

if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY=OFF") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin8, HIGH);
}
 
// IF LED10=OFF turn it OFF
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY=ON") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin8, LOW);
}

  
    // check if valid tcp data is received
    if (pos) {
        char* data = (char *) Ethernet::buffer + pos;
        if (strncmp("GET / ", data, 6) == 0) {

            ether.httpServerReplyAck();
             // send ack to the request
            for (int i = 0; i < sizeof(pageSegments)/sizeof(pageSegments[0]); i++){
              char buffer[700];
              if (i != 11){
                
          
                Serial.println(sizeof(pageSegments));
                Serial.println(sizeof((char*)pgm_read_word(&pageSegments[0])));
                strlcpy_P(buffer,(char*)pgm_read_word(&pageSegments[i]),700);
                Serial.println(buffer);
                memcpy_P(ether.tcpOffset(), buffer, 700); // send first packet and not send the terminate flag
                ether.httpServerReply_with_flags(700,TCP_FLAGS_ACK_V);
              } 
              else if ( i == 11){
                Serial.println(sizeof(pageSegments));
                Serial.println(sizeof((char*)pgm_read_word(&pageSegments[0])));
                strlcpy_P(buffer,(char*)pgm_read_word(&pageSegments[i]),700);
                Serial.println(buffer);
                  memcpy_P(ether.tcpOffset(), buffer, 700); // send first packet and not send the terminate flag
                 ether.httpServerReply_with_flags(700 - 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V); }
              }

            }
            // memcpy_P(ether.tcpOffset(), pageSeg1, sizeof pageSeg1); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg1 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg2, sizeof pageSeg2); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg2 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg3, sizeof pageSeg3); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg3 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg4, sizeof pageSeg4); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg4 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg5, sizeof pageSeg5); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg5 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg6, sizeof pageSeg6); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg6 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg7, sizeof pageSeg7); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg7 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg8, sizeof pageSeg8); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg8 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg9, sizeof pageSeg9); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg9 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg10, sizeof pageSeg10); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg10 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg11, sizeof pageSeg11); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg11 - 1,TCP_FLAGS_ACK_V);
            // memcpy_P(ether.tcpOffset(), pageSeg12, sizeof pageSeg12); // send first packet and not send the terminate flag
            // ether.httpServerReply_with_flags(sizeof pageSeg12 - 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V); }
        else
        {
            char buffer[500];

            ether.httpServerReplyAck(); // send ack to the request
              Serial.println(sizeof(pageSegments));
                Serial.println(sizeof((char*)pgm_read_word(&pageSegments[0])));
                strlcpy_P(buffer,(char*)pgm_read_word(&pageSegments[0]),700);
                Serial.println(buffer);
            memcpy_P(ether.tcpOffset(), buffer, 700);//only the first part will sended
            ether.httpServerReply_with_flags(700 - 1,TCP_FLAGS_ACK_V|TCP_FLAGS_FIN_V);
        }
  }
}
