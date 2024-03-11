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

#include "nittcMega.h"

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
  