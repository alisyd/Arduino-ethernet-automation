
void setup(){
  Serial.begin(9600);
}
void loop (){
  float V2 = 0;
  float Vsquare = 0;
  int x  = 0;
  float v = 0;

for(int i = 0; i<2000; i++){
  x = analogRead(A1)-512;

  //v = 0.00000412*x*x*x - 0.000857*x*x+2.675*x-3.198;
  v = 2.700*x - 6.025;
  V2 = v*v;

  Vsquare = Vsquare +V2;
  delay(0.01);
}
float vrms = sqrt(Vsquare/2000);
Serial.println(vrms);
delay(2000);
}