#include <EtherCard.h>
byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
const char host[] PROGMEM = "192.168.1.10";
static byte session;
byte Ethernet::buffer[700];
Stash stash;
void setup () {
Serial.begin(9600);
Serial.println("[CPU Monitor]");
if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
Serial.println(F("[ERROR] Failed to access Ethernet Controller."));
if (!ether.dhcpSetup())
Serial.println(F("[ERROR] DHCP Connection Failure."));
ether.hisport = 50000;
char websiteIp[] = "10.13.100.141";
ether.parseIp(ether.hisip, websiteIp);
ether.printIp("[INFO] My IP: ", ether.myip);
ether.printIp("[INFO] Gateway: ", ether.gwip);
ether.printIp("[INFO] DNS Server: ", ether.dnsip);
//ether.dnsLookup(host);
ether.printIp("[INFO] CPU Host IP: ", ether.hisip);
Serial.println("\n[INFO] Connecting to CPU Monitor Server...");
session = ether.tcpSend();
ether.persistTcpConnection(false);
}
void loop () {
ether.packetLoop(ether.packetReceive());
 byte reply = ether.tcpReply(session);
if (reply != 0) {
Serial.println("Load: ");
Serial.println((char *)reply);
}
}