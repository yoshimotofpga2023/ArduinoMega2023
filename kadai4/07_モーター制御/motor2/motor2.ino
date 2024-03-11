// Timer5の比較一致割り込みを設定してAD変換を開始させる

#include <LiquidCrystal.h>

#define input1_pin 8
#define input2_pin 7
#define input3_pin 6
#define input4_pin 5

#define led_pin1 A8
#define led_pin2 A9
#define led_pin3 A10
#define led_pin4 A11

//#define BRINK_INTERVAL 250 

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);


const int INPUT_PIN = A0;    // 入力ピンをA0に固定
//unsigned long VOLUME;                  // 変数を整数型で宣言
int ad_data;
float v_data;

int LEDx;
int mv;

int ad_0;
int ad_1;
int ad_2;
int ad_3;
int ad_4;
int ad_5;
int ad_6;
int ad_7;

void setup() {

  pinMode(INPUT_PIN, INPUT);
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(led_pin1,OUTPUT) ;
  pinMode(led_pin2,OUTPUT) ;
  pinMode(led_pin3,OUTPUT) ;
  pinMode(led_pin4,OUTPUT) ;

  pinMode(A2, INPUT);
  //pinMode(3,OUTPUT) ;

  Serial.begin(9600);



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

 // LEDx=HIGH;
 lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
}


// Timer5の比較一致割り込みハンドラ
ISR(TIMER5_COMPA_vect) {
//ad_data = analogRead(INPUT_PIN);


  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む

  if(status4==1){
    mv = 300;
  }else{
    mv = 800;
  }

  OCR1A = mv;
  OCR3B = mv;

ad_7 = ad_6;
ad_6 = ad_5;
ad_5 = ad_4;
ad_4 = ad_3;
ad_3 = ad_2;
ad_2 = ad_1;
ad_1 = ad_0;
ad_0 = analogRead(A2);

ad_data = (ad_0 + ad_1 + ad_2 + ad_3 + ad_4 + ad_5 + ad_6 + ad_7) >>3;

//  v_data = ad_data * 4888.0 /1000000.0;
/*
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
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
*/

//  Serial.println(ad_data);
//  Serial.println(v_data);
//  delay(100);  

/*
digitalWrite( 3, LEDx );
LEDx =!LEDx;
*/
}

void loop() {

 
   lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("mv");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("ad_data=");  // 文字の表示
  lcd.setCursor(10, 0);
  lcd.print(mv); 
  lcd.setCursor(10, 1);
  lcd.print(ad_data); 
  //lcd.setCursor(14, 1);
  //lcd.print("V");
  delay(100); 

}




