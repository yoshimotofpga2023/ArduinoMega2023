/*
    フィードバック制御の実装 for Arduino Mega
    ┗ PI制御を用いてモーター発電量の目標値に追従するようにゲインを調整する．


    The circuit:
    * 各inputに接続されているコンポーネントのリスト
    * 各outputに接続されているコンポーネントのリスト

    Created R6.02.01
    By 
    Modified 
    By 

    URL:

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(35, 23, 33, 25, 31, 27, 29);

int Target;
int kp;
int ki;
int status1, status2, status3, status4 ;
int ad_data;
long MV;
long en;
long MVp;
long MVi;
long di;
long MVi_pre;


void setup() {

  pinMode(8 ,INPUT) ;
  pinMode(7 ,INPUT) ; 
  pinMode(6 ,INPUT) ;
  pinMode(5 ,INPUT) ;
  pinMode(A2, INPUT);

  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.begin(9600);

  // Timer5の設定
  TCCR5A  = 0;
  TCCR5B  = 0;
  TCCR5B |= (1 << WGM52) | (1 << CS50);  //CTCmode //prescaler to 1
  OCR5A   = 8000; // 0.5ms割り込み周期
  TIMSK5 |= (1 << OCIE5A);

  // Timer1を停止
  TCCR1A = 0; // Timer1のレジスタAを0に設定
  TCCR1B = 0; // Timer1のレジスタBを0に設定

  // フェーズと周波数の調整を設定 (mode 14)
  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  TCCR1A |= (1 << WGM11);

  // クロック選択とプリスケーラの設定 (ここではプリスケーラを1に設定)
  TCCR1B |= (1 << CS10); 

  // ICR1にトップ値を設定 (PWM周波数を決定)
  ICR1 = 1024; // ここでPWMの周波数を設定

  // ノンインバーティングモードでPWMを有効化
  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << COM1B1); 


  // Timer3の設定
  TCCR3A = 0; // TCCR3Aレジスタを初期化
  TCCR3B = 0; // TCCR3Bレジスタを初期化
  TCNT3  = 0; // タイマーのカウンタ値を0にリセット

  // ノンインバーティングモードでPWMを設定（チャネルB）
  TCCR3A |= (1 << COM3B1);
  // ファストPWMモードを設定（ICR3をトップ値とする）
  TCCR3A |= (1 << WGM31);
  TCCR3B |= (1 << WGM32) | (1 << WGM33);
  
  // クロック選択とプリスケーラの設定（プリスケーラを1に設定）
   TCCR3B |= (1 << CS30);

  // PWMの周波数を設定するためのICR3の値を設定
  ICR3 = 1024; // 

 lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
}

// Timer5の比較一致割り込み
ISR(TIMER5_COMPA_vect) {
  status1 = digitalRead(8) ; //スイッチの状態を読む
  status2 = digitalRead(7) ; //スイッチの状態を読む
  status3 = digitalRead(6) ; //スイッチの状態を読む
  status4 = digitalRead(5) ; //スイッチの状態を読む

  ad_data  = analogRead(A2);
  en = Target - ad_data;
  MVp = kp * en/10;
  di = ki * en/100;
  MVi = di + MVi_pre;
  MV = MVp + MVi;
  MVi_pre = MVi;
  
  if(MV>1000){
    MV=1000;
  }
  if(MV<0){
    MV=0;
  }

  OCR3B = MV;       //ポート2に出力
  OCR1A = Target;   //ポート11に出力
  OCR1B = ad_data;  //ポート12に出力
}

void loop() {
    if(status4){
    Target = 400;
  }else{
    Target = 200;
  }

  if(status3){
    if(status1){
      kp = kp + 1;
    }
    if(status2){
      if(kp == 0){
        kp = 0;
      }else{
        kp = kp - 1;
      }
    }
    lcd.clear();               // LCD画面をクリア
    lcd.setCursor(0, 1);       // カーソルの位置を指定
    lcd.print("*kp=  ");       // 文字の表示
    lcd.setCursor(5, 1);
    lcd.print(kp); 
    lcd.setCursor(8, 1);       // カーソルの位置を指定
    lcd.print(" ki= ");  // 文字の表示
    lcd.setCursor(12, 1);
    lcd.print(ki); 
  }else{
    if(status1){
      ki = ki + 1;
    }
    if(status2){
      if(ki == 0){
        ki = 0;
      }else{
        ki = ki - 1;
      }
    }
    lcd.clear();               // LCD画面をクリア
    lcd.setCursor(0, 1);       // カーソルの位置を指定
    lcd.print(" kp=  ");       // 文字の表示
    lcd.setCursor(5, 1);
    lcd.print(kp); 
    lcd.setCursor(8, 1);       // カーソルの位置を指定
    lcd.print("*ki= ");  // 文字の表示
    lcd.setCursor(12, 1);
    lcd.print(ki); 
  }
lcd.setCursor(0, 0);       // カーソルの位置を指定
  lcd.print("T=  ");       // 文字の表示
  lcd.setCursor(3, 0);
  lcd.print(Target); 
  lcd.setCursor(8, 0);       // カーソルの位置を指定
  lcd.print("D= ");  // 文字の表示
  lcd.setCursor(10, 0);
  lcd.print(ad_data); 
 
  delay(10); 
}
