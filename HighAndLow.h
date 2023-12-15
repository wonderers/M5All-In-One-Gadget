/* インクルードガード */
#pragma once
#include <Arduino.h>
#include <M5Stack.h>
#include "MdDateTime.h"
#include "M5All-In-One-Gadget.h"
#include "CSV_Parser.h"

typedef enum {
    BIG,
    SMALL
} HighLowSelect;

typedef enum {
    ONEMORE,
    BACK
} Continue;

typedef enum {
    START,
    MENUBACK,
    RECORD
} HALTitleState;

class HighAndLow // classの定義
{
private: // privateはクラス内からしかアクセスできない
    HALTitleState m_highandlow_title_state=MENUBACK;
    int m_left_card=0;
    int m_right_card=0;
    bool m_win_judgement;
    int m_win_count=0;
    int m_win_log=0;
    HighLowSelect m_select;
    Continue m_continue;
public: // publicはどこからでもアクセス可能
    HALTitleState getHALTitleState();
    void setHALTitleState(HALTitleState hts);
    int getLeftCard();
    void setLeftCard(int lc);
    int getRightCard();
    void setRightCard(int rc);
    bool getWinJudgement();
    void setWinJudgement(bool wj);
    int getWinCount();
    void setWinCount(int wc);
    int getWinLog();
    void setWinLog(int wl);
    HighLowSelect getSelect();
    void setSelect(HighLowSelect hls);
    Continue getContinue();
    void setContinue(Continue cnt);
    int randomCard();
    void leftCard();
    void rightCard(); 
    void gameJudgement();
    void writeWinLog ();
    String createWinLog();
    void displayRecordText(String text, int x, int y);
    void displayRecordLog();
    void writesd();
    void readsd();
};