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

#include "nittcMega.h"

int output = 0;
int count = 244;

void setup() {
    pinMode( LED1, OUTPUT );
    pinMode( LED2, OUTPUT );
    pinMode( LED3, OUTPUT );
    pinMode( LED4, OUTPUT );
    resisterSetting();  

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
