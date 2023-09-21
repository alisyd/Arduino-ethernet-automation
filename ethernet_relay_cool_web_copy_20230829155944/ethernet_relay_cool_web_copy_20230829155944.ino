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
char const websiteContent[] PROGMEM =
"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Sensor Data Page</title>hello";
uint16_t websiteLength = sizeof(websiteContent) - 1;



void setup(){
pinMode(ledPin8, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
Serial.println("\n[backSoon]");
//Serial.println(sizeof );
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
 

void loop() {
  ether.packetLoop(ether.packetReceive());

  if (ether.clientWaitingGw()) {
    ether.copyIp(ether.hisip, ether.myip);
    
    // Send segments of the website content
    static uint16_t sentBytes = 0;
    uint16_t remainingBytes = websiteLength - sentBytes;
    if (remainingBytes > 0) {
      uint16_t bytesToSend = min(remainingBytes, Ethernet::buffer);
      
      // Modify the Ethernet buffer with segment data
      memcpy_P(ether.tcpOffset(), websiteContent + sentBytes, bytesToSend);
      ether.buildTcpData(sizeof(websiteContent), bytesToSend);
      ether.sendTcpData();

      sentBytes += bytesToSend;
    } else {
      // Send empty response to signal the end
      ether.buildTcpData(0, 0);
      ether.sendTcpData();

      sentBytes = 0; // Reset for the next request
    }
  }
}

