#include <EtherCard.h>
#include <bufferfiller.h>
#include <enc28j60.h>
#include <net.h>
#include <stash.h>




#define STATIC 0 // set to 1 to disable DHCP (adjust myip/gwip values below)
 
int ledPin8 = 8;
#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
//static byte myip[] = { 0, 0, 0, 0 }; // 0.0.0.0 for DHCP
byte Ethernet::buffer[1000];
char const page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>Sensor Data Page</title>"
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
  ".info-text {"
    "display: none;"
    "margin-top: 10px;"
    "padding: 10px;"
    "background-color: #f9f9f9;"
    "border-radius: 5px;"
  "}"
"</style>"
"</head>"
"<body>"
"<div class=\"container\">"
  "<div class=\"sensor-box\">"
    "<h2>Sensor Data</h2>"
    "<p><strong>Voltage:</strong> <span id=\"voltage\">0 V</span></p>"
    "<p><strong>Current:</strong> <span id=\"current\">0 A</span></p>"
  "</div>"
  
  "<div class=\"toggle-container\">"
    "<label class=\"radio-label\">Toggle Sensor:</label>"
    "<label class=\"toggle-button-label\" for=\"sensorToggle\">"
      "<input type=\"checkbox\" id=\"sensorToggle\">"
      "<div class=\"toggle-button\"></div>"
    "</label>"
  "</div>"
  
  "<button class=\"info-button\" id=\"infoBtn\">Info</button>"
  "<div class=\"info-text\" id=\"infoText\">"
    "This is some additional information about the sensor data and its usage."
  "</div>"
"</div>"

"<script>"
  "const voltageElement = document.getElementById('voltage');"
  "const currentElement = document.getElementById('current');"
  "const sensorToggle = document.getElementById('sensorToggle');"
  "const infoBtn = document.getElementById('infoBtn');"
  "const infoText = document.getElementById('infoText');"
  
  "// Simulate sensor data update"
  "setInterval(() => {"
    "if (sensorToggle.checked) {"
      "const voltage = Math.random() * 5;"
      "const current = Math.random() * 2;"
      "voltageElement.textContent = voltage.toFixed(2) + ' V';"
      "currentElement.textContent = current.toFixed(2) + ' A';"
    "} else {"
      "voltageElement.textContent = '0 V';"
      "currentElement.textContent = '0 A';"
    "}"
  "}, 2000);"
  
  "// Show info text"
  "infoBtn.addEventListener('click', () => {"
    "infoText.style.display = 'block';"
  "});"
"</script>"
"</body>"
"</html>"
"<button><a href=\"/?RELAY=ON\" style=\"text-decoration = none;\">ON</a></button>"
"<button><a href=\"/?RELAY=OFF\" style=\"text-decoration = none;\">OFF</a></button>"
;

void setup(){
pinMode(ledPin8, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
Serial.println("\n[backSoon]");
Serial.println("starting to check for ethernet controller\n");
if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
Serial.println( "Failed to access Ethernet controller\n");
#if STATIC
ether.staticSetup(myip, gwip);
#else
if (!ether.dhcpSetup())
Serial.println("DHCP failed");
#endif
 
ether.printIp("IP: ", ether.myip);
ether.printIp("GW: ", ether.gwip);
ether.printIp("DNS: ", ether.dnsip);
}
 
void loop(){
// wait for an incoming TCP packet, but ignore its contents
//if (ether.packetLoop(ether.packetReceive())) {
//memcpy_P(ether.tcpOffset(), page, sizeof page);
//ether.httpServerReply(sizeof page - 1);
word len = ether.packetReceive();
word pos = ether.packetLoop(len);
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY=OFF") != 0) {
Serial.println("Received ON command");
digitalWrite(ledPin8, HIGH);
}
 
// IF LED10=OFF turn it OFF
if(strstr((char *)Ethernet::buffer + pos, "GET /?RELAY=ON") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin8, LOW);
}
 
// show some data to the user
memcpy_P(ether.tcpOffset(), page, sizeof page);
ether.httpServerReply(sizeof page - 1);
}


void blinkLed(){
while (true){
digitalWrite(LED_BUILTIN, HIGH);
delay(500);
digitalWrite(LED_BUILTIN, LOW);
delay(500);
}
}

