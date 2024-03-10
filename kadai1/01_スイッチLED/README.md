# LED点灯プログラム

## 概要
* arduinoを用いてLEDの点灯を行うプログラムを作成する。Arduinoでのプログラミング方法やマイコンを用いたLED点灯回路の設計概要を学ぶ。

## シミュレーション
* 回路図（ブレッドボード配線）例

![switch_led]( "switch_led")

## メモ
* プログラム

トグルスイッチとタクトスイッチに連動して４つのLEDを点灯・消灯させる

``` k0101_LED.ino

/*
    スイッチ連動LED点灯 for Arduino Mega
    |_ SWと連動してLEDが点灯点滅するプログラム


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:https://www.tinkercad.com/things/lSnLkh15ZDH-k0101akadai1arduino

*/


const int = ledPin1 A8;
const int = ledPin2 A9;
const int = ledPin3 A10;
const int = ledPin4 A11;

const int inputPin1 = 8;
const int inputPin2 = 7;
const int inputPin3 = 6;
const int inputPin4 = 5;

void setup() {
  pinMode( inputPin1, INPUT );
  pinMode( ledPin1, OUTPUT );
  pinMode( inputPin2, INPUT );
  pinMode( ledPin2, OUTPUT );
  pinMode( inputPin3, INPUT );
  pinMode( ledPin3, OUTPUT );
  pinMode( inputPin4, INPUT );
  pinMode( ledPin4, OUTPUT );

}

void loop() {

  // スイッチ1の状態でLED1の点灯状況を決める
 if(digitalRead(inputPin1)== 1){
  digitalWrite( ledPin1, HIGH );
  }
 else{
  digitalWrite( ledPin1, LOW );
 }

  // スイッチ2の状態でLED2の点灯状況を決める
  if(digitalRead(inputPin2)== 1){
  digitalWrite( ledPin2, HIGH );
  }
 else{
  digitalWrite( ledPin2, LOW );
 }

  // スイッチ3の状態でLED3の点灯状況を決める
  if(digitalRead(inputPin3)== 1){
  digitalWrite( ledPin3, HIGH );
  }
 else{
  digitalWrite( ledPin3, LOW );
 }

  // スイッチ4の状態でLED4の点灯状況を決める
  if(digitalRead(inputPin4)== 1){
  digitalWrite( ledPin4, HIGH );
  }
 else{
  digitalWrite( ledPin4, LOW );
 }

}


```

## シミュレーション for ArduinoMega

### wokwi
 ![wokwi_switchled]( "wokwi_switchled")

### SimuLIDE
 ![siml_switchled]( "siml_switchled")