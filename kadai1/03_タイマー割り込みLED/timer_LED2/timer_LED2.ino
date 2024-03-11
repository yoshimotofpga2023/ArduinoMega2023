/*
    スイッチ連動LED点灯 for Arduino Mega
    |_ SWと連動してLEDが点灯点滅するプログラム


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.03.10
    By 
    Modified 
    By 

    URL:

*/


#define LED1 A8 
#define sw1 8
#define LED2 A9
#define sw2 7
#define LED3 A10
#define sw3 6
#define LED4 A11
#define sw4 5

int output = 0;
int count = 244;

void setup() {
  pinMode( LED1, OUTPUT );
  pinMode( LED2, OUTPUT );
  pinMode( LED3, OUTPUT );
  pinMode( LED4, OUTPUT );


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

  if(count == 0){
    digitalWrite( LED1, output );
    output =!output;
    count =244;
  }else{
    count -= 1; 
  }
 
}


void loop() {

}
