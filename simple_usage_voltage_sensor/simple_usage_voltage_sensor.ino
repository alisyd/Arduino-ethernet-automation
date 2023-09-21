/**
 * This program shows you how to use the basics of this library.
*/

#include <ZMPT101B.h>

#define SENSITIVITY 674.75000f

// ZMPT101B sensor output connected to analog pin A0
// and the voltage source frequency is 50 Hz.
ZMPT101B voltageSensor(A1, 50.0);

void setup() {
  Serial.begin(9600);
  // Change the sensitivity value based on value you got from the calibrate
  // example.
  voltageSensor.setSensitivity(SENSITIVITY);
}

void loop() {
  // read the voltage and then print via Serial.
  float voltage = voltageSensor.getRmsVoltage();
  Serial.println(voltage);

  delay(1000);
}
