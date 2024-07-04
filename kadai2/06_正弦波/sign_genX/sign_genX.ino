/*
    正弦波発生プログラム for Arduino Mega

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

const int nWave = 1024;
const int stepDiv = 8;

unsigned long VOLUME;                  // 変数を整数型で宣言
unsigned int step;
unsigned int wave[nWave];

volatile unsigned int i_wave;
volatile float unit_deg = (2.0 * 3.141592) / nWave;

int ad_0, ad_1, ad_2, ad_3;
int ad_data;

LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

void setup(){
  int i;
  i_wave = 0;
  step = 0;
  unit_deg = 0;

  pinMode(A0, INPUT);
  pinMode(8,INPUT) ;
  pinMode(7,INPUT) ; 
  pinMode(6,INPUT) ;
  pinMode(5,INPUT) ;

  Serial.begin(115200);

  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 1// 1分周
  OCR5A   = 8000;  // 0.5ms割り込み周期//1/16MHz*8000=5ms
  TIMSK5 |= (1 << OCIE5A); //タイマー5スタート
  
  // Timer1の設定(タイマー1でPWMを生成する)
  // ピン11と12でPWM出力を有効化
  pinMode(11, OUTPUT); //正弦波出力
  pinMode(12, OUTPUT); //デジタルフィルタで使用

  // Timer1を停止
  TCCR1A = 0; // Timer1のレジスタAを0に設定
  TCCR1B = 0; // Timer1のレジスタBを0に設定

  // フェーズと周波数の調整を設定
  //ICR1が上限値のPWMモードICR1がマッチした時にタイマーをクリア
  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  TCCR1A |= (1 << WGM11);

  // クロック選択とプリスケーラの設定 (ここではプリスケーラを1に設定＝分周比1)
  TCCR1B |= (1 << CS10); //クロック周波数16MHz

  // ICR1にトップ値を設定 (PWM周波数を決定)
  ICR1 = 2047; // ここでPWMの周波数を設定，このぎり波の最大値に相当。

  // ノンインバーティングモードでPWMを有効化
  TCCR1A |= (1 << COM1A1); // ピン11を使用
  TCCR1A |= (1 << COM1B1); // ピン12を使用

  step = 1;
  unit_deg = (2.0 * 3.141592) / nWave;

//sin波配列の生成
  for (i = 0; i < nWave; i++)
  {
    wave[i] = (unsigned int)((((sin(unit_deg * (float) i )+ 1.0)/ 2.0 )* 2047.0 ) + 0.5);
  }
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
}

ISR (TIMER5_COMPA_vect) {
  unsigned int w;
  unsigned int phase;
  unsigned float frq;

  VOLUME = analogRead(A0);  // アナログ値の読み取り
  step = VOLUME / stepDiv;
  
  if(step<1){
    step =1;
  }else if(step>127){
    step = 127;
  }

  i_wave += step; //i_wave = i_wave + stepと同じ意味
  if (i_wave >= nWave){
  	i_wave = 0;
  } 

  w = wave[i_wave]; //sin波瞬時値の導出

  ad_3 = ad_2;
  ad_2 = ad_1;
  ad_1 = ad_0;
  ad_0 = w;

  //デジタルフィルタ (1+Z^(-1)+Z^(-2)+Z^(-3))/4
  ad_data = (ad_0 + ad_1 + ad_2 + ad_3) >>2;

  if(w<1023){
    phase = 0 ;
  }else{
    phase = 2047 ; 
  }


  OCR1A = w; // のこぎり波比較の指令値
  OCR1B = phase;
  frq = (1.0/(0.5e-3*1024)*step);
}

void loop(){
  lcd.clear();               // LCD画面をクリア
  delay(100);  

}
