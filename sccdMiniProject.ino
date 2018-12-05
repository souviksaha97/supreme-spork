#include <LCD5110_Basic.h>


LCD5110 myGLCD(7,6,5,3,4);
extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];

float digVal1 = 0;
float tempVal1 = 0;
float sensorVol1 = 0;
float digVal2 = 0;
float tempVal2 = 0;
float sensorVol2 = 0;

float avgVal = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A5, OUTPUT);
  //analogWrite(A1, 41);
  myGLCD.InitLCD();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digVal1 = analogRead(A0);
  digVal2 = analogRead(A1);
  
  sensorVol1 = digVal1/204.8;
  tempVal1 = (sensorVol1*10) + 20;
  
  sensorVol2 = digVal2/204.8;
  tempVal2 = (sensorVol2*10) + 20;
  
  Serial.print(tempVal1);
  Serial.print(" ");
  Serial.print(tempVal2);
  Serial.println();

  avgVal = 0.5*(tempVal1+tempVal2);
  myGLCD.setFont(SmallFont);
  myGLCD.print("TEMPERATURE", CENTER, 0);
  myGLCD.setFont(BigNumbers);
  myGLCD.printNumF(avgVal, 3, CENTER, 20);
  
  if (avgVal > 50)
  {
    tone(13, 131);
    analogWrite(A5, 1023);
  }
  else if (avgVal > 65)
    tone(13, 262);
  else
  {
    analogWrite(A5, 0);
    noTone(13);
  }
  delay(1000);
  myGLCD.clrScr();
}
