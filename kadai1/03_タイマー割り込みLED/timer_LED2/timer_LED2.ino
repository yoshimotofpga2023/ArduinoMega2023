/*
    タイマー割り込みLED点滅① for Arduino Mega
    |_ タイマー割り込み処理でLEDを点滅させるプログラム
    |_ タイマー5の割り込み処理


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputLEDに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:

*/

const int ledPin1 =  A8;
const int ledPin2 =  A9;
const int ledPin3 =  A10;
const int ledPin4 =  A11;

const int inputPin1 = 8;
const int inputPin2 = 7;
const int inputPin3 = 6;
const int inputPin4 = 5;

int outputLED = 0;
int timertimerCount = 244;

void setup() {
  pinMode( ledPin1, OUTPUT );
  pinMode( ledPin2, OUTPUT );
  pinMode( ledPin3, OUTPUT );
  pinMode( ledPin4, OUTPUT );


  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 1
//  TCCR5B |= (1 << WGM52) | (1 << CS51);  //CTCmode //prescaler to 8
//  TCCR5B |= (1 << WGM52) | (1 << CS50)| (1 << CS51) ;  //CTCmode //prescaler to 64
  OCR5A   = 65535;  // 4.096ms割り込み周期
//  OCR5A   = 32767; // 2.048ms割り込み周期
// OCR5A   = 8191; // 0.512ms割り込み周期
//    OCR5A   = 2047;  // 0.128ms割り込み周期
   TIMSK5 |= (1 << OCIE5A);

}

ISR (TIMER5_COMPA_vect) {

  if(timerCount == 0){
    digitalWrite( ledPin1, outputLED );
    outputLED =!outputLED;
    timerCount =244;
  }else{
    timerCount -= 1; 
  }
 
}


void loop() {

}
