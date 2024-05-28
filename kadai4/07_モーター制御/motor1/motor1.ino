/*
    可変抵抗調整によるモーター駆動 for Arduino Mega
    ┗ モーターを可変抵抗の入力値に応じたスピードで駆動する


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

const int input1Pin = 8;
const int input1Pin = 7;
const int input1Pin = 6;
const int input1Pin = 5;

const int led1Pin = A8;
const int led2Pin = A9;
const int led3Pin = A10;
const int led4Pin = A11;
const int inputPin = A0;    // 入力ピンをA0に固定

volatile int ad_data;
volatile float v_data;

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

void setup() {

  pinMode(inputPin, INPUT);
  pinMode(input1Pin,INPUT) ;
  pinMode(input2Pin,INPUT) ; 
  pinMode(input3Pin,INPUT) ;
  pinMode(input4Pin,INPUT) ;
  
  pinMode(led1Pin,OUTPUT) ;
  pinMode(led2Pin,OUTPUT) ;
  pinMode(led3Pin,OUTPUT) ;
  pinMode(led4Pin,OUTPUT) ;

  Serial.begin(9600);
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)

/*
  // AD変換の設定
  ADMUX = 0; // ADC0を選択、参照電圧はAVcc
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // AD変換を有効化、割り込みを有効化、プリスケーラを設定
*/

  // Timer5の設定
  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 1
//   TCCR5B |= (1 << WGM52) | (1 << CS51);  //CTCmode //prescaler to 8
//  TCCR5B |= (1 << WGM52) | (1 << CS50)| (1 << CS51) ;  //CTCmode //prescaler to 64
//  OCR5A   = 65535;  // 4.096ms割り込み周期
//  OCR5A   = 32767; // 2.048ms割り込み周期
  OCR5A   = 8191; // 0.512ms割り込み周期
//   OCR5A   = 2047;  // 0.128ms割り込み周期
   TIMSK5 |= (1 << OCIE5A);

  // Timer1の設定
  // ピン11と12でPWM出力を有効化
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // Timer1を停止
  TCCR1A = 0; // Timer1のレジスタAを0に設定
  TCCR1B = 0; // Timer1のレジスタBを0に設定

  // フェーズと周波数の調整を設定 (mode 14)
  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  TCCR1A |= (1 << WGM11);

  // クロック選択とプリスケーラの設定 (ここではプリスケーラを1に設定)
  TCCR1B |= (1 << CS10); 

  // ICR1にトップ値を設定 (PWM周波数を決定)
  ICR1 = 1024; // ここでPWMの周波数を設定


// PWMのデューティサイクルを設定
  // OCR1A (ピン11のデューティサイクル)
//  OCR1A = 1024; // デューティサイクルを50%に設定

  // OCR1B (ピン12のデューティサイクル、使用する場合)
  // OCR1B = 1024; // デューティサイクルを50%に設定 (必要に応じて変更)

  // ノンインバーティングモードでPWMを有効化
  TCCR1A |= (1 << COM1A1);
  // TCCR1A |= (1 << COM1B1); // ピン12を使用する場合はコメントを外す


  // ピン2を出力として設定
  pinMode(2, OUTPUT);

  // Timer3の設定
  TCCR3A = 0; // TCCR3Aレジスタを初期化
  TCCR3B = 0; // TCCR3Bレジスタを初期化
  TCNT3  = 0; // タイマーのカウンタ値を0にリセット

  // ノンインバーティングモードでPWMを設定（チャネルB）
  TCCR3A |= (1 << COM3B1);
  // ファストPWMモードを設定（ICR3をトップ値とする）
  TCCR3A |= (1 << WGM31);
  TCCR3B |= (1 << WGM32) | (1 << WGM33);
  
  // クロック選択とプリスケーラの設定（プリスケーラを1に設定）
   TCCR3B |= (1 << CS30);

  // PWMの周波数を設定するためのICR3の値を設定
  ICR3 = 1024; // 

  // デューティサイクルを約50%に設定（チャネルB）
  //OCR3B = 2604;

}


// Timer5の比較一致割り込みハンドラ
ISR(TIMER5_COMPA_vect) {
  int status1, status2, status3, status4 ;

  ad_data = analogRead(inputPin);

  OCR1A = ad_data;
  OCR3B = ad_data;

  status1 = digitalRead(input1Pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2Pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3Pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4Pin) ; //スイッチの状態を読む

  v_data = ad_data * 4888.0 /1000000.0;
}

void loop() {
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("ad_data");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("INPUT V=");  // 文字の表示
  lcd.setCursor(10, 0);
  lcd.print(ad_data); 
  lcd.setCursor(10, 1);
  lcd.print(v_data); 
  lcd.setCursor(14, 1);
  lcd.print("V");
  delay(10); 

}




