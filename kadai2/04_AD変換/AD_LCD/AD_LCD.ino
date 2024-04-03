/*
    AD変換による電圧表示 for Arduino Mega
    |_ AD変換で取得した値を電圧値に表示する


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputLEDに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:

*/


#include <LiquidCrystal.h>
const int volumeSocket1 = A0;
const int analogVal;
const float inputVolt;

LiquidCrystal lcd( 35, 23, 33, 25, 31, 27, 29 );

void setup() {
  lcd.begin( 16, 2 );
  lcd.clear();
}

void loop() {
  lcd.clear();

  analogVal = analogRead(VolumeSocket1);
  inputVolt = analogVal * 5.0 / 1023.0;

  lcd.setCursor(0, 0);
  lcd.print("Analog_val");
  lcd.setCursor(11, 0);
  lcd.print(analogVal);
  lcd.setCursor(0, 1);
  lcd.print("Input_volt");
  lcd.setCursor(11, 1);
  lcd.print(inputVolt);  
  lcd.setCursor(15, 1);
  lcd.print("V");
  delay( 5 );

}
