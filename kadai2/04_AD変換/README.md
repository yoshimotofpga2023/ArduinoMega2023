# AD変換による電圧値の取得

## 概要
* 可変抵抗で5Vの電圧を可変させ取得できるAD変換値を再度電圧値に変換する。

## メモ
* AD変換の割り込みは使用せず、メイン文で直接AD変換値を取得している。

 * ソースコード
 ```
/*
    AD変換による電圧表示 for Arduino Mega
    └ AD変換で取得した値を電圧値に表示する


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


 ```

## シミュレーション for ArduinoMega

### wokwi
 未検証．

### SimuLIDE
 ![2bunshu](./pic_ADConv/simIK020201.png "pinAssign")

 ![2bunshu](./pic_ADConv/simIK020202.png "pinAssign")