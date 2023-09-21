void setup() {
  Serial.begin(9600); //Start Serial Monitor to display current read value on Serial monitor
}

void loop(){
float  sumSqr=0.0, meanSqr=0.0, currentRMS=0.0;
for(int i=0; i <= 200; i++){
  float sensorValue = analogRead(A0);
  float current =(2500-(sensorValue/1023)*5000.0)/185;
  sumSqr+=current*current;
  delay(3);
}
meanSqr = sumSqr/200;
currentRMS = sqrt(meanSqr);
Serial.println(currentRMS,7);

  //Get 150 samples
  //AcsValue = analogRead(A0);
  // Serial.println(AcsValue);
  // Serial.println(AcsValue/1023*5000);
  // Serial.println(2500-AcsValue/1023*5000.0);
  //Serial.println((2500-(AcsValue/1023)*5000)/185, 4);



//Print the read current on Serial monitor
delay(1000);
}