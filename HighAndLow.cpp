#include "HighAndLow.h"

int HighAndLow::getLeftCard() {
  return m_left_card;
}

void HighAndLow::setLeftCard(int lc) {
  m_left_card = lc;
}

int HighAndLow::getRightCard() {
  return m_right_card;
}

void HighAndLow::setRightCard(int rc) {
  m_right_card = rc;
}

bool HighAndLow::getWinJudgement() {
  return m_win_judgement;
}

void HighAndLow::setWinJudgement(bool wj) {
  m_win_judgement = wj;
}

int HighAndLow::getWinCount(){
    return m_win_count;
}

void HighAndLow::setWinCount(int wc) {
  m_win_count = wc;
}

int HighAndLow::getWinLog(){
    return m_win_log;
}

void HighAndLow::setWinLog(int wl){
    m_win_log=wl;
}

void HighAndLow::setSelect(HighLowSelect hls){
    m_select=hls;
}

HighLowSelect HighAndLow::getSelect(){
    return m_select;
}

int HighAndLow::randomCard(){  
    randomSeed(0);
    int randNumber = random(0, 9);
    return randNumber;    
}

void HighAndLow::leftCard(){
    setLeftCard(randomCard());
}

void HighAndLow::rightCard(){
    do{
        setRightCard(randomCard());
    }while((getLeftCard())==(getRightCard()));
}

void HighAndLow::gameJudgement(){
    if(getLeftCard() > getRightCard()){
        if(getSelect()==SMALL){
            setWinJudgement(true);
            int wincount=(getWinCount())+1;
            setWinCount(wincount);
        }else if(getSelect()==BIG){
            setWinJudgement(false);
        }else{    
        }
    }
    if(getLeftCard() < getRightCard()){
        if(getSelect()==BIG){
            setWinJudgement(true);
            int wincount=(getWinCount())+1;
            setWinCount(wincount);
        }else if(getSelect()==SMALL){
            setWinJudgement(false);
        }else{    
        }
    }
}
