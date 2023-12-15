#ifdef ARDUINO_ARCH_AVR
  #include <avr/wdt.h> // for self reset
  // const char* BIN_FILENAME = "FIRMWARE.BIN"; // expected by zevero avr_boot
#endif

int ResetPin = 4;
int EthCS = 6;
int EthTrig = 8;
int relayTrig =7;
void setup() {  
 // Set digital pin to 5V
  pinMode(ResetPin, OUTPUT);
  pinMode(EthCS, OUTPUT);
  pinMode(EthTrig, INPUT);
  pinMode(relayTrig, OUTPUT);
  digitalWrite(ResetPin, HIGH);
  digitalWrite(EthCS, HIGH);
  digitalWrite(relayTrig, HIGH);
  Serial.println(MCUCR);
  
   // Set the digital pin to an OUTPUT pin
  Serial.begin(9600);
  Serial.println("Inside the setup");
}
void loop() 
{
  // A little fun countdown!  3..2..1

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
    if (command == temp){
      Serial.println("Recieved command reset");
      Serial.println("Disabling the Ethernet module");
      digitalWrite(EthCS, LOW);
      digitalWrite(ResetPin, LOW);
      delay(30000);
      digitalWrite(ResetPin, HIGH);
      int val = digitalRead(EthTrig);
      while( val != HIGH){
        val = digitalRead(EthTrig);
        Serial.println("Did not recieve Trig");
      }
      Serial.println("Recieved Trigger");
    digitalWrite(EthCS, HIGH);

    }
    if (command == 's'){
      Serial.println("Triggering the reset");
      // digitalWrite(ResetPin, HIGH);
      delay(1000);
    // MCUSR = (1<<EXTRF);
    // digitalWrite(relayTrig, LOW);
    // delay(10000);
    // digitalWrite(relayTrig, HIGH);



      reset_to_bootloader();
      // #ifdef __AVR__
      //   Serial.println("Disabling Watchdog timer");
      //   wdt_disable();  /* Disable the watchdog and wait for more than 2 seconds */
      //   delay(3000);
      //   wdt_enable(WDTO_8S);
      //   Serial.println("Enabled watchdog timer");
      //   while (true);
      // #else
      //   NVIC_SystemReset();
      // #endif
    }
  }

}

void reset_to_bootloader() {
    // see 11.2.2 MCUCR – MCU Control Register
    // Enable change of interrupt vectors
    // MCUSR = (1<<BORF);
    // MCUSR = (1<<EXTRF);
    MCUCR = (1<<IVCE);
    // Move interrupts to Boot Flash section
    MCUCR = (1<<IVSEL);

    // enable watchdog timer
    wdt_enable(WDTO_15MS);

    // block waiting for the watchdog to timeout and jump to the bootloader
    while(1);

    // Move interrupts to Boot Flash section
    // MCUCR = (1<<IVSEL);
    
    // block waiting for the watchdog to timeout and jump to the bootloader
    // while(1){
    //   Serial.println("inside the while, in reset code");
    // }
}
  // digitalWrite(ResetPin, LOW); // This command grouunds the reset pin and reboots the Arduino
  // Serial.println("If it worked, the Arduino will never output this line!");
