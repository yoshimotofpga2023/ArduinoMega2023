#include <LiquidCrystal.h>

#define input1_pin 7
#define input2_pin 6
#define input3_pin 5
#define input4_pin 4

#define led_pin1 10
#define led_pin2 11
#define led_pin3 12
#define led_pin4 13

#define PWM_GEN 12
#define PWM_MOTOR 2

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
int VOLUME;                  // 変数を整数型で宣言
unsigned long v_data;
unsigned int ad_motor;

void setup(){
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(led_pin1,OUTPUT) ;
  pinMode(led_pin2,OUTPUT) ;
  pinMode(led_pin3,OUTPUT) ;
  pinMode(led_pin4,OUTPUT) ;
  
  pinMode(PWM_MOTOR, OUTPUT);
    
  Serial.begin(115200);
  
  
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("Hello!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示
}

void loop(){
  int status1, status2, status3, status4 ;
  status1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  status2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  status3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  status4 = digitalRead(input4_pin) ; //スイッチの状態を読む
  
  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り
  
  v_data = VOLUME * 4888;
  v_data = v_data / 1000;
  ad_motor = VOLUME / 4;

  Serial.println(ad_motor);
  analogWrite(PWM_MOTOR, ad_motor);
 
//  delay(100);
  
}