/*
    タイマー割り込みによるLチカ for Arduino Mega
    |_ SWと連動してLEDが点灯点滅するプログラム


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.02.01
    By S.YOSHIMOTO
    Modified 
    By 

    URL:

*/

#include <LiquidCrystal.h>

#define input1_pin 8
#define input2_pin 7
#define input3_pin 6
#define input4_pin 5

#define led_pin1 A8
#define led_pin2 A9
#define led_pin3 A10
#define led_pin4 A11

#define BRINK_INTERVAL 250 

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
int VOLUME;                  // 変数を整数型で宣言
unsigned long v_data;
unsigned int Timer1_tick;	// Timer1の割り込み回数を数える変数

void setup(){
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(led_pin1,OUTPUT) ;
  pinMode(led_pin2,OUTPUT) ;
  pinMode(led_pin3,OUTPUT) ;
  pinMode(led_pin4,OUTPUT) ;
  
  
  Serial.begin(115200);

  TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12);  //CTCmode //prescaler to 256
//  OCR1A   = 65535;
  OCR1A   = 255;
  TIMSK1 |= (1 << OCIE1A);
  
  
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("Hello!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示

  digitalWrite(led_pin1, LOW);
  digitalWrite(led_pin2, HIGH);

}

ISR (TIMER1_COMPA_vect) {

  int s12, s13;
  s13 = digitalRead(led_pin1);
  s12 = digitalRead(led_pin2);

  if (Timer1_tick < BRINK_INTERVAL){
    Timer1_tick++;
  } else {
	Serial.println(millis());
    digitalWrite(led_pin1, !(digitalRead(led_pin1)));
    digitalWrite(led_pin2, !(digitalRead(led_pin2)));
    Timer1_tick = 0;
  }

}


void loop(){
  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む


  
  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り
  
  v_data = VOLUME * 4888;
  v_data = v_data / 1000;
  
//  Serial.print("Volume: ");        // シリアルモニタに出力
//  Serial.println(VOLUME);
//  Serial.print("Volt: ");        // シリアルモニタに出力
//  Serial.println(v_data);
 
//  delay(100);
  
}
