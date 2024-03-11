/*
    タイマー割り込みLED点滅① for Arduino Mega
    |_ タイマー割り込み処理でLEDを点滅させるプログラム
    |_FlexTimer2ライブラリを使用


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:

*/

#include <FlexiTimer2.h>

const int ledPin1 =  A8;
const int ledPin2 =  A9;
const int ledPin3 =  A10;
const int ledPin4 =  A11;

const int inputPin1 = 8;
const int inputPin2 = 7;
const int inputPin3 = 6;
const int inputPin4 = 5;

void swLed(){
  static boolean output = HIGH;
  digitalWrite( ledPin1, output );
  output =!output;
}


void setup() {
  pinMode( ledPin1, OUTPUT );

  FlexiTimer2::set(500, swLed);
  FlexiTimer2::start();  
}

void loop() {

}
