/* インクルードガード */
#pragma once
#include <Arduino.h>
#include <M5Stack.h>

typedef enum {
    BIG,
    SMALL
} HighLowSelect;

class HighAndLow // classの定義
{
private: // privateはクラス内からしかアクセスできない
    int m_left_card=0;
    int m_right_card=0;
    bool m_win_judgement;
    int m_win_count=0;
    int m_win_log=0;
    HighLowSelect m_select;
public: // publicはどこからでもアクセス可能
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
    void setSelect(HighLowSelect hls);
    HighLowSelect getSelect();
    int randomCard();
    void leftCard();
    void rightCard(); 
    void gameJudgement();
};