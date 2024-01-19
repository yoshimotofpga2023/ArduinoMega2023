#include <LiquidCrystal.h>

#define input1_pin 8 //Tact01 
#define input2_pin 7 //Tact02
#define input3_pin 6 //Toggle01
#define input4_pin 5 //Toggle02

#define LED_D1 A8
#define LED_D2 A9
#define LED_D3 A10
#define LED_D4 A11
#define LED_D5 3

#define Motor_Input A2
#define Motor_PWM 2
#define PWM_GEN 12

#define VON 200
#define VOFF 75

// LCDディスプレイ設定
LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

const int INPUT_PIN = A0;    // 入力ピンをA0に固定
int VOLUME;                  // 変数を整数型で宣言
unsigned long v_data;

int pwm_op;
int chatt01, chatt02;

void setup(){
  pinMode(input1_pin,INPUT) ;
  pinMode(input2_pin,INPUT) ; 
  pinMode(input3_pin,INPUT) ;
  pinMode(input4_pin,INPUT) ;
  
  pinMode(LED_D1,OUTPUT) ;
  pinMode(LED_D2,OUTPUT) ;
  pinMode(LED_D3,OUTPUT) ;
  pinMode(LED_D4,OUTPUT) ;

  pinMode(Motor_Input,INPUT) ;
  pinMode(Motor_PWM,OUTPUT) ;

  Serial.begin(115200);
    
  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア
  lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("Hello!");       // 文字の表示
  lcd.setCursor(0, 1);       // カーソルの位置を指定
  lcd.print("NITTC ARDUINO");  // 文字の表示

  pwm_op = 0;
  chatt01 = 0;
  chatt02 = 0;
}

void loop(){
  int state1, state2, state3, state4 ;
  unsigned int m_input;
  unsigned int target;

  state1 = digitalRead(input1_pin) ; //スイッチの状態を読む
  state2 = digitalRead(input2_pin) ; //スイッチの状態を読む
  state3 = digitalRead(input3_pin) ; //スイッチの状態を読む
  state4 = digitalRead(input4_pin) ; //スイッチの状態を読む

  if(state1 == HIGH && chatt01 == 0){
    chatt01 = 1;
  }else{
    if(state1 == LOW && chatt01 == 1){
      pwm_op = pwm_op + 10;
      if(pwm_op > 250){
        pwm_op = 255;
      }
      analogWrite(Motor_PWM, pwm_op);
      chatt01 = 0;
    }
  }

  if(state2 == HIGH && chatt02 == 0){
    chatt02 = 1;
  }else{
    if(state2 == LOW && chatt02 == 1){
      pwm_op = pwm_op - 10;
      if(pwm_op < 11){
        pwm_op = 10;
      }
      analogWrite(Motor_PWM, pwm_op);
      chatt02 = 0;
    }
  }

    Serial.print("ope: ");
    Serial.println(pwm_op);

  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り
  
  v_data = VOLUME * 4888;
  v_data = v_data / 1000;
  //Serial.plint("VOL: ");
  //Serial.println(VOLUME);

  m_input = analogRead(Motor_Input);
  Serial.print("MotorInput: ");
  Serial.println(m_input);

  if (state3 == HIGH){
    target = 800;
  } else {
    target = 300;
  }

  if (m_input < target){
    analogWrite(Motor_PWM, VON);
  } else {
    analogWrite(Motor_PWM, VOFF);    
  }

  //delay(500);
  
}