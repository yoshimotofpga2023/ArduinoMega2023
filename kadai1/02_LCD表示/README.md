# SWによるLED点灯プログラム

## 概要
* arduinoを用いてスイッチからの入出力を連動するプログラムを作成する。

## メモ

 * ソースコード
 ```
/*
    LCD表示 for Arduino Mega
    |_ LCDに文字列を表示する


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd( 35, 23, 33, 25, 31, 27, 29 );

void setup() {
  lcd.begin( 16, 2 );
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(5, 1);
  lcd.print("NITTC!");
}

void loop() {
 
}
  

 ```

## シミュレーション
* 回路図（ブレッドボード配線）例

![2bunshu](./pic_LCD/K0102_LCD.png  "pinAssign")

## シミュレーション for ArduinoMega

### wokwi
 ![2bunshu](./pic_LCD/wokwiK0102.png "pinAssign")

### SimuLIDE
 ![2bunshu](./pic_LCD/simIK0102.png "pinAssign")