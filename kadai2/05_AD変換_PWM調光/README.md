# LEDのPWMによる調光実験

 * ソースコード
 ```
/*
    PWMによるLED調光 for Arduino Mega
    |_ AD変換で取得した値をに応じたPWMでLEDを釣行する


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
const int ledSocket = 11;

int analogVal;
float inputVolt;
float pwmREF;
int ledLight = 0;

LiquidCrystal lcd( 35, 23, 33, 25, 31, 27, 29 );

void setup() {
  pinMode( ledSocket, OUTPUT ); //出力ポート設定
  lcd.begin( 16, 2 );
  lcd.clear();
}

void loop() {
  lcd.clear();

  analogVal = analogRead(VolumeSocket1);
  inputVolt = analogVal * 5.0 / 1023.0;

  pwmREF = analogVal/4.0 ; //最大値を255に合わせる。

  lcd.setCursor(0, 0);
  lcd.print("PWM_REF");
  lcd.setCursor(11, 0);
  lcd.print(pwmREF);
  lcd.setCursor(0, 1);
  lcd.print("Input_volt");
  lcd.setCursor(11, 1);
  lcd.print(inputVolt);  
  lcd.setCursor(15, 1);
  lcd.print("V");

  analogWrite( ledSocket, pwmREF ); //PWM出力
  delay( 50 );

}


 ```

## シミュレーション




