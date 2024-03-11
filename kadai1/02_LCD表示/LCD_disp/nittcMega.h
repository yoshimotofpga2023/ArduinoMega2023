#ifndef __NITTCMEGA_H__
#define __NITTCMEGA_H__
 
#include "Arduino.h"
#include <LiquidCrystal.h> 

// 入出力ポートの割当て
const int ledPin1 =  A8;
const int ledPin2 =  A9;
const int ledPin3 =  A10;
const int ledPin4 =  A11;

const int inputPin1 = 8;
const int inputPin2 = 7;
const int inputPin3 = 6;
const int inputPin4 = 5;

// プロトタイプ宣言
void resisterSetting();

void setup();
void loop();
 
#endif /* __NITTCMEGA_H__ */