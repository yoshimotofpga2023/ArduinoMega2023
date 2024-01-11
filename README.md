# Cyclone10実験予備実験メモ

## 概要
* ４Eで扱う実験課題を大まかに分けて検証しています。

## 現実験との相違点
* FPGAボードをCyclone ⅡからCyclone 10LPへ変更
* Quartusのバージョンの違いにより波形シミュレーションソフトが組み込まれていないので
QuartusPrimeから直接連携できる、ModelSimというシミュレーションソフトを使用する。
    * 波形ソフトはテストベンチが必要（Verilog HDLで検証）
    * テストベンチはQuartusで作成可能。テキストエディタもQuartusPrimeで起動可能。
* ボードの変更により書き込みソフトをQuartusPrimeに組み込まれているソフト(Programmer)を使用する。  
