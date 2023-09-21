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
byte Ethernet::buffer[700];
char const page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
"<head><title>"
"Service Temporarily Unavailable"
"</title></head>"
"<body>"
"<h3>This page is used behind the scene</h3>"
"<p><em>"
"Commands to control LED are transferred to Arduino.<br />"
"The syntax:  or ON"
"</em></p>"
"</body>"
"</html>"
;

void setup(){
pinMode(ledPin8, OUTPUT);
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
digitalWrite(ledPin8, HIGH);
delay(500);
digitalWrite(ledPin8, LOW);
delay(500);
}
}

