
#include <stdlib.h>
float current;
float voltage;

int countDigits(float fnum, int prec) {
  int count = 0;
  int num = fnum * prec;
  while (num != 0) {
    count += 1;
    num = num / 10;
  }
  if (count == 3) {
    count += 2;
  } else if (count > 3) {
    count += 1;
  }
  return count;
}

char * formatCV(float current, float voltage) {
  int cSize = countDigits(current, 1000);
  int vSize = countDigits(voltage, 100);
  // Serial.println(cSize);
  // Serial.println(vSize);
  static char cBuff[10];
  static char vBuff[10];
  static char cvBuff[50];

  dtostrf(current, cSize, 3, cBuff);
  dtostrf(voltage, vSize, 2, vBuff);
  for (int i = 0; i < cSize; i++) {
    cvBuff[i] = cBuff[i];
  }
  cvBuff[cSize] = ':';
  for (int i = 0; i < vSize; i++) {
    cvBuff[i + cSize + 1] = vBuff[i];
  }
  cvBuff[vSize+cSize+1] = "\0";
  // Serial.println(cvBuff);
  // if (strcmp(cvBuff, "0.445:230.00")==0){
  //   Serial.println("Correct match");
  // }
 
  return cvBuff;
}
void setup() {
  Serial.begin(9600);
  current = 0.445;
  voltage = 230.00;
}


void loop() { 
  char * buff = formatCV(current,voltage);
  if (strcmp(buff, "0.445:230.0")==0){
    Serial.println("Correct match");
  }
  Serial.println(buff);
  }
  //   if (strcmp(formatCV(current,voltage), "0.445:230.00")==0) {

  //   Serial.println("Correctly formatted");
  // }
  // int cSize = countDigits(current, 1000);
  // int vSize = countDigits(voltage, 100);
  // Serial.println(cSize);
  // Serial.println(vSize);
  // char cBuff[cSize];
  // char vBuff[vSize];
  // char cvBuff[cSize + vSize + 1];

  // dtostrf(current, cSize, 3, cBuff);
  // Serial.println(cBuff);
  // // for (int i = 0; i < cSize; i++){
  // //   Serial.println(cBuff[i]);

  // // }
  // // strcpy(cvBuff, cBuff);
  // // strcat(cvBuff, ":");
  // dtostrf(voltage, vSize, 2, vBuff);
  // Serial.println(vBuff);
  // // cBuff[0]= "0";
  // for (int i = 0; i < cSize; i++) {
  //   cvBuff[i] = cBuff[i];
  //   // Serial.println(cvBuff[i]);
  // }
  // Serial.print(cBuff[0]);
  // Serial.print(cvBuff[0]);

  // cvBuff[cSize] = ':';
  // // Serial.println(cvBuff[cSize]);
  // for (int i = 0; i < vSize; i++) {
  //   cvBuff[i + cSize + 1] = vBuff[i];
  // }
  // for (int i = 0; i < cSize + vSize + 1; i++) {
  //   // Serial.print(cvBuff[i]);
  //   Serial.flush();
  //   Serial.print(cvBuff[i]);
  //   Serial.flush();
  // }
  // Serial.println();
  // Serial.flush();
  // if (strcmp(cvBuff, "0.445:230.00")) {

  //   Serial.println("Zero Detected");
  // }
  // Serial.println(cvBuff);
  // strcpy(cvBuff,vBuff);
  // for (int i =0; i<= cSize; i++){

  //   if(!(isDigit(cBuff[i])) && !(cBuff[i] == '.' )){
  //     cBuff[i]=':';
  //     Serial.println(cBuff[i]);
  //     break;
  //   // Serial.println(cBuff[i]);
  //   }
  //   Serial.println(cBuff[i]);
  //   // Serial.println(cBuff[i]);
  // }
  // Serial.println(cBuff);
  // Serial.write(cBuff);
// }
