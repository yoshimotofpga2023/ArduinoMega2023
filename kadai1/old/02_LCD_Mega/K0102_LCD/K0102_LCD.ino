/*
    LCDに文字列を表示するプログラム


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.02.01
    By S.YOSHIMOTO
    Modified 
    By 

    URL:https://www.tinkercad.com/things/alDiMlQtxvt-k0102kadai1arduinorev00

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

#define BRINK_INTERVAL 250 // タイマー文周用カウンタ

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
int VOLUME;                  // 変数を整数型で宣言
unsigned long v_data;
unsigned int Timer1_tick;  // Timer1の割り込み回数を数える変数

void setup(){
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(led_pin1,OUTPUT) ;
  pinMode(led_pin2,OUTPUT) ;
  pinMode(led_pin3,OUTPUT) ;
  pinMode(led_pin4,OUTPUT) ;  
  
  Serial.begin(9600);

  TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12);  //CTCmode //prescaler to 1
  OCR1A   = 255;
  TIMSK1 |= (1 << OCIE1A);  
  
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("K0102!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示
  
  delay(1000);

}

ISR (TIMER1_COMPA_vect) {

  /*
  タイマー1によるタイマー割り込み処理
  */

}



void loop(){
  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む

  /*
  なにもしない．setup関数で実行された処理を継続する．
  */
}
