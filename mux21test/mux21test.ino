

int S0 = 6;
int SIG = 7;

void setup() {
  // put your setup code here, to run once:
    // pinMode(ResetPin, OUTPUT);
    pinMode(S0, OUTPUT);
    pinMode(SIG, OUTPUT);
    
   // Set the digital pin to an OUTPUT pin
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println("Checking for a serial command");
  delay(5000);
  while(Serial.available() > 0){
    char command = Serial.read();
    Serial.println(command);
    if (command == 's'){
      Serial.println("Recieved command select 0 and set high");
      // digitalWrite(S0, LOW);
      delay(1000);
      digitalWrite(SIG, HIGH);
    }
    if (command == 'o'){
      Serial.println("Recieved command select 1 and set high");
      digitalWrite(S0, HIGH);
      delay(1000);
      digitalWrite(SIG, HIGH);
    }
    if (command == 'a'){
      Serial.println("Recieved command select 0 and set LOW");
      digitalWrite(S0, LOW);
      delay(1000);
      digitalWrite(SIG, LOW);
    }
    if (command == 'b'){
      Serial.println("Recieved command select 1 and set low");
      digitalWrite(S0, HIGH);
      delay(1000);
      digitalWrite(SIG, LOW);
    }

}
}
