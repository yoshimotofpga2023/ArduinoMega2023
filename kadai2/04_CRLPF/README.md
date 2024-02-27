# CRローパスフィルタ特性測定実験

## 概要
* 11kΩと22kΩの抵抗(R)と0.1uのコンデンサで作成したRCフィルタ回路で正弦波を観測し平滑化された正弦波の周波数特性、位相特性を調べる。

## メモ
* 割り込み周期は、0.000625msで測定

## 特性測定例
* 周波数特性
 ![top](./pic_CRLPF/22k_CRLPFPower.png "top")
 ![top](./pic_CRLPF/11k_CRLPFPower.png "top")

* 位相特性
 ![top](./pic_CRLPF/22k_CRLPFPhase.png "top")
 ![top](./pic_CRLPF/11k_CRLPFPhase.png "top")
 ※かなり怪しいので要検証


## シミュレーション for ArduinoMega

### wokwi
 未検証．

### SimuLIDE
 ![2bunshu](./pic_CRLPF/simIKadai0301.png "pinAssign")

 ![2bunshu](./pic_CRLPF/simIKadai0302.png "pinAssign")

 ![2bunshu](./pic_CRLPF/simIKadai0303.png "pinAssign")

 ![2bunshu](./pic_CRLPF/simIKadai0304.png "pinAssign")

 ![2bunshu](./pic_CRLPF/simIKadai0305.png "pinAssign")

