# 移動平均デジタルローパスフィルタ特性測定実験

## 概要
* 4点移動平均と8点移動平均のデジタルフィルタを実装し、
各移動平均ごとの周波数特性、位相特性を調べる。

## メモ
* 割り込み周期は、0.512msで測定

## 特性測定例
* 4点移動平均

※特に位相特性が理論値通りでないので8点平均までは実施せず。プログラム中にはコメントアウトで実装している。

 ** 周波数特性

 ![power_4](./picDF/DFLPFpower_4.png "power_4")

 ** 位相特性

 ![phase_4](./picDF/DFLPFphase_4.png "phase_4")

 * 8点移動平均

 ** 周波数特性

 ![power_8](./picDF/DFLPFpower_8.png "power_8")

 ** 位相特性

 ![phase_8](./picDF/DFLPFphase_8.png "phase_8")

 ## シミュレーション for ArduinoMega

### wokwi
 未検証．

### SimuLIDE
 ![2bunshu](./picDF/simIK0801.png "pinAssign")


 ![2bunshu](./picDF/simIK0802.png "pinAssign")