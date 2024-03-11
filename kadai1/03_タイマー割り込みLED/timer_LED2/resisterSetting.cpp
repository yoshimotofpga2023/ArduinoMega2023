
#include "nittcMega.h"

// 割り込みタイマー５レジスタ設定
void resisterSetting(){
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