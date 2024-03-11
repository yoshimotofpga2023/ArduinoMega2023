/*
    PWMによるLED調光 for Arduino Mega
    |_ AD変換で取得した値をに応じたPWMでLEDを釣行する


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.02.01
    By 
    Modified 
    By 

    URL:

*/

#include <LiquidCrystal.h>
#define VolumeSocket1 A1
#define LED_Socket 3
int LED_light = 0;
LiquidCrystal lcd( 35, 23, 33, 25, 31, 27, 29 );

void setup() {
  pinMode( LED_Socket, OUTPUT );
  lcd.begin( 16, 2 );
  lcd.clear();
}

void loop() {
  lcd.clear();
  #define Analogval (analogRead(VolumeSocket1))
  #define Inputvolt (Analogval*5.0/1023.0)
  int PWM_REF (Analogval/4.0);
  lcd.setCursor(0, 0);
  lcd.print("PWM_REF");
  lcd.setCursor(11, 0);
  lcd.print(PWM_REF);
  lcd.setCursor(0, 1);
  lcd.print("Input_volt");
  lcd.setCursor(11, 1);
  lcd.print(Inputvolt);  
  lcd.setCursor(15, 1);
  lcd.print("V");

  analogWrite( LED_Socket, PWM_REF );
  delay( 50 );

}
