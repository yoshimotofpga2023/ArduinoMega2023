#include <LiquidCrystal.h>

#define PIN_SIN_WAVE 3
#define N_WAVE 1024
#define step_div 8

#define input1_pin 7
#define input2_pin 6
#define input3_pin 5
#define input4_pin 4

#define led_pin1 10
#define led_pin2 A9
#define led_pin3 A10
#define led_pin4 13

#define sine_gen 12
#define PWM_GEN 11

#define BRINK_INTERVAL 250 

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
unsigned long VOLUME;                  // 変数を整数型で宣言
unsigned int step;
unsigned int Timer1_tick;	// Timer1の割り込み回数を数える変数

unsigned int wave[N_WAVE];

volatile unsigned int i_wave;
volatile float unit_deg = (2.0 * 3.141592) / N_WAVE;

void setup(){

  int i;
  i_wave = 0;
  step = 0;
  unit_deg = 0;

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

  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 1
//  TCCR5B |= (1 << WGM52) | (1 << CS51);  //CTCmode //prescaler to 8
//  TCCR5B |= (1 << WGM52) | (1 << CS50)| (1 << CS51) ;  //CTCmode //prescaler to 64
  OCR5A   = 65535;  // 4.096ms割り込み周期
//  OCR5A   = 32767; // 2.048ms割り込み周期
//  OCR5A   = 8191; // 0.512ms割り込み周期
//  OCR5A   = 1023; 
  TIMSK5 |= (1 << OCIE5A);
  

  TCCR1A = (1 << COM1B1) | (0 << COM1B0) | (1 << WGM12) | (1 << WGM10);
  TCCR1B = (1 << CS10);
  
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("Hello!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示


  step = 1;
  unit_deg = (2.0 * 3.141592) / N_WAVE;
  for (i = 0; i < N_WAVE; i++)
  {
    wave[i] = (unsigned int)((((sin(unit_deg * (float) i )+ 1.0)/ 2.0 )* 255.0 ) + 0.5);
  }
}

ISR (TIMER5_COMPA_vect) {
  unsigned int w;

  if (i_wave >= N_WAVE){
  	i_wave = 0;
  } 

  w = wave[i_wave];
  analogWrite(sine_gen, wave[i_wave]);  // D12
//  analogWrite(PWM_GEN, wave[i_wave]);  // D11
//  Serial.println(w);
  i_wave = i_wave + step;
//  i_wave++;

}


void loop(){
  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む

  //  Serial.println(status1) ;

  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む


  
  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り

  step = VOLUME / (float) step_div;
  if(step < 1){
    step = 1;
  } else if(step >  127){
    step = 127;
  }

  Serial.println(VOLUME);
  Serial.println(step);
//  Serial.println("D: " + VOLUME);
//  Serial.println("step: " + step);
  delay(100);  
}