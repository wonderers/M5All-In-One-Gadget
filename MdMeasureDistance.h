/* インクルードガード */
#pragma once
#include <M5Stack.h>
#include <Arduino.h>
#include "M5All-In-One-Gadget.h"
#include "DrUltraSonic.h"

class MdMeasureDistance // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    double getDistance();
};
