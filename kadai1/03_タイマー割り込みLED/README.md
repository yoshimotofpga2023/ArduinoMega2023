# 1秒周期LED点滅作成実験

## 概要
* 割り込みタイマーで1秒周期の割り込みを作成し２つのLEDを１秒周期で交互に点滅させる。

## メモ
* Timer1を使用。Timer1は16bitタイマーなので1周期は65536カウント。（16Mhzクロックなので、1割り込み周期4msくらい）
* Timer1のタイマーカウントを256カウントに変更して、分周を256を使用。（32分周がないため）
* 4.096ms割り込み周期となるため、1秒は250回（BRINK_INTERVAL)としている。

 * ソースコード
 ```
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


 ```

## シミュレーション for ArduinoMega

### wokwi
 ![2bunshu](./pic_OneSecTimer/wokwiK0201.png "pinAssign")

### SimuLIDE
 ![2bunshu](./pic_OneSecTimer/simIK0201.png "pinAssign")

 ![2bunshu](./pic_OneSecTimer/k0201MOV.gif "pinAssign")
