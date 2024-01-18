#include <LiquidCrystal.h>

#define N_WAVE 128
#define step_div 64
#define sine_gen 12
#define PWM_GEN 11

#define BRINK_INTERVAL 250 // LED点滅Timerカウンタ

#define input1_pin 6
#define input2_pin 5
#define input3_pin 8
#define input4_pin 7

#define led_pin1 A8
#define led_pin2 A9
#define led_pin3 A10
#define led_pin4 A11
#define led_pin5 3

// LCDディスプレイ設定
LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
unsigned long VOLUME;        // 可変抵抗AD値取得用
unsigned int step;           // SIN波テーブルステップ計算用
unsigned int Timer1_tick;	// Timer1の割り込み回数を数える変数

unsigned int wave[N_WAVE];    // SIN波テーブル

volatile unsigned int i_wave;  // SIN位相
volatile float unit_deg = (2.0 * 3.141592) / N_WAVE;  // SIN位相デジタル単位

void setup(){

  int i;
  i_wave = 0;
  step = 0;
  unit_deg = 0;

  // アナログ・デジタル入出力設定
  pinMode(INPUT_PIN, INPUT);
  
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(led_pin1,OUTPUT) ;
  pinMode(led_pin2,OUTPUT) ;
  pinMode(led_pin3,OUTPUT) ;
  pinMode(led_pin4,OUTPUT) ;
  
  pinMode(PIN_SIN_WAVE, OUTPUT);
  pinMode(sine_gen, OUTPUT);

  Serial.begin(115200);

  // 割り込みタイマー用
  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 256
  OCR5A   = 19999; // 6Hz
//  OCR5A   = 9999;  // 12Hz
//  OCR5A   = 4999;    //25Hz
  TIMSK5 |= (1 << OCIE5A);

  // PWM出力用 対応ピン：D11、D12  
  TCCR1A = (1 << COM1B1) | (0 << COM1B0) | (1 << WGM12) | (1 << WGM10);
  TCCR1B = (1 << CS10);
  
  // LCD初期化
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("Hello!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示


  // SIN波テーブル作成 : N_WAVE数SIN波離散化
  step = 1;
  unit_deg = (2.0 * 3.141592) / N_WAVE;
  for (i = 0; i < N_WAVE; i++)
  {
    wave[i] = (unsigned int)((((sin(unit_deg * (float) i )+ 1.0)/ 2.0 )* 255.0 ) + 0.5);
  }

}

// タイマー割り込み処理
ISR (TIMER5_COMPA_vect) {
  unsigned int w;
  if (i_wave >= N_WAVE){
  	i_wave = 0;
  } 

  if (i_wave < N_WAVE/2){
    analogWrite(PWM_GEN, 255);
  } else {
    analogWrite(PWM_GEN, 0);
  }
  w = wave[i_wave];
  analogWrite(sine_gen, w);
//  Serial.println(w);
  i_wave = i_wave + step;

}


void loop(){
  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む

  
  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り
  step = VOLUME / (float) step_div; // ステップ数（短冊の幅）計算

  if(step < 1){
    step = 1;
  } else if(step >  15){
    step = 16 -1;
  }

  Serial.println(step);
  delay(100);  
}