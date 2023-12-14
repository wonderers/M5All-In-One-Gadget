/* インクルードガード */
#pragma once
#include <M5Stack.h>
#include <Arduino.h>
#include "DrTHSensor.h"
#include "M5All-In-One-Gadget.h"

class MdWBGTMonitor // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void init();
    void getWBGT(double* tempuerture,double* humidity,WbgtIndex* index);
};
