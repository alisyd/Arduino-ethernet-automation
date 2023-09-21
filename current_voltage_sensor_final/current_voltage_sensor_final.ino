
#include <ZMPT101B.h>
#define SENSITIVITY 674.75000f

ZMPT101B voltageSensor(A1, 50.0);

void setup() {
  Serial.begin(9600); //Start Serial Monitor to display current read value on Serial monitor
  voltageSensor.setSensitivity(SENSITIVITY);

}

void loop(){
// float  sumSqr=0.0, meanSqr=0.0, currentRMS=0.0;
// float voltage = 0.0;
// for(int i=0; i <= 200; i++){
//   float sensorValue = analogRead(A0);
//   float current =(2500-(sensorValue/1023)*5000.0)/185;
//   sumSqr+=current*current;
//   delay(3);
// }
// meanSqr = sumSqr/200;
// currentRMS = sqrt(meanSqr);
// voltage = voltageSensor.getRmsVoltage();
Serial.println("current:");
Serial.println(measureCurrent(A0),7);
Serial.println("Voltage:");
Serial.println(measureVoltage(A1));



  //Get 150 samples
  //AcsValue = analogRead(A0);
  // Serial.println(AcsValue);
  // Serial.println(AcsValue/1023*5000);
  // Serial.println(2500-AcsValue/1023*5000.0);
  //Serial.println((2500-(AcsValue/1023)*5000)/185, 4);



//Print the read current on Serial monitor
delay(1000);
}

float measureVoltage(uint8_t pin){
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
