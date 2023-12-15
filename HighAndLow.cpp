#include "HighAndLow.h"

MdDateTime halmdtime;

HALTitleState HighAndLow::getHALTitleState(){
    return m_highandlow_title_state;
}

void HighAndLow::setHALTitleState(HALTitleState hts){
    m_highandlow_title_state=hts;
}

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

HighLowSelect HighAndLow::getSelect(){
    return m_select;
}

void HighAndLow::setSelect(HighLowSelect hls){
    m_select=hls;
}

Continue HighAndLow::getContinue(){
    return m_continue;
}

void HighAndLow::setContinue(Continue cnt){
    m_continue=cnt;
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
            setWinLog(getWinCount());
            setWinCount(0);
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
            setWinLog(getWinCount());
            setWinCount(0);
        }else{    
        }
    }
}

void HighAndLow::writeWinLog (){
    if(getWinJudgement()){
        if(getContinue()==BACK){
            
        }
    }else{

    }
}

String HighAndLow::createWinLog(){
    String stringdate=String(halmdtime.readDate());
    String stringtime=String(halmdtime.readTime());
    String stringwinlog=String(getWinLog());
    String stringsentence=String("straight wins");
    String history=String(stringdate+" "+stringtime+" "+stringwinlog+" "+stringsentence);
    return history;
}

void HighAndLow::displayRecordText(String text, int x, int y)
{
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(0x0000, 0xFFFF);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print(text);
}

void HighAndLow::displayRecordLog(){
    for(int i=0 ; i<10 ;i++){
        displayRecordText(createWinLog(), HIGHANDLOW_RECORD_TEXT_X_CRD, HIGHANDLOW_RECORD_TEXT_Y_CRD+(i*10));
    }
}

void HighAndLow::writesd(){
    M5.begin();
    File myFile = SD.open("/record.txt", FILE_WRITE);
      if (myFile) {
            myFile.print(createWinLog());
        } else {
            displayRecordText("error opening record.txt", HIGHANDLOW_RECORD_TEXT_X_CRD, HIGHANDLOW_RECORD_TEXT_Y_CRD);
        }
        myFile.close();
}


void HighAndLow::readsd(){
    M5.begin();
  M5.Lcd.setTextSize(1);
  // ファイルオープン
  File myFile = SD.open("/record.txt");
  
  if (myFile) {
    unsigned int auiSize = 0;
    unsigned int auiCnt = 0;
    auiSize = myFile.size();
    // サイズ分ループ
    for( auiCnt = 0; auiCnt < auiSize; auiCnt++ )
    {
      // ファイルの中身を表示
      myFile.seek(auiCnt);
      M5.Lcd.printf("%c",myFile.read());
    }
    // ファイルクローズ   
    myFile.close();
  } else {
    displayRecordText("File open error record.txt", HIGHANDLOW_RECORD_TEXT_X_CRD, HIGHANDLOW_RECORD_TEXT_Y_CRD);
  }
    /*
    M5.begin();
    File myFile = SD.open("/record.txt", FILE_READ);
    while (myFile.available()) {
      displayRecordText(myFile.read(), HIGHANDLOW_RECORD_TEXT_X_CRD, HIGHANDLOW_RECORD_TEXT_Y_CRD);
    }
    myFile.close();
    */
}
