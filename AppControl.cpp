#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;
HighAndLow highandlow;

const char *g_str_orange[] = {
  COMMON_ORANGE0_IMG_PATH,
  COMMON_ORANGE1_IMG_PATH,
  COMMON_ORANGE2_IMG_PATH,
  COMMON_ORANGE3_IMG_PATH,
  COMMON_ORANGE4_IMG_PATH,
  COMMON_ORANGE5_IMG_PATH,
  COMMON_ORANGE6_IMG_PATH,
  COMMON_ORANGE7_IMG_PATH,
  COMMON_ORANGE8_IMG_PATH,
  COMMON_ORANGE9_IMG_PATH,
};

const char *g_str_blue[] = {
  COMMON_BLUE0_IMG_PATH,
  COMMON_BLUE1_IMG_PATH,
  COMMON_BLUE2_IMG_PATH,
  COMMON_BLUE3_IMG_PATH,
  COMMON_BLUE4_IMG_PATH,
  COMMON_BLUE5_IMG_PATH,
  COMMON_BLUE6_IMG_PATH,
  COMMON_BLUE7_IMG_PATH,
  COMMON_BLUE8_IMG_PATH,
  COMMON_BLUE9_IMG_PATH,
};

const char *g_str_heart[] = {
  HIGHANDLOW_HEART1_IMG_PATH,
  HIGHANDLOW_HEART2_IMG_PATH,
  HIGHANDLOW_HEART3_IMG_PATH,
  HIGHANDLOW_HEART4_IMG_PATH,
  HIGHANDLOW_HEART5_IMG_PATH,
  HIGHANDLOW_HEART6_IMG_PATH,
  HIGHANDLOW_HEART7_IMG_PATH,
  HIGHANDLOW_HEART8_IMG_PATH,
  HIGHANDLOW_HEART9_IMG_PATH,
};

const char *g_str_spade[] = {
  HIGHANDLOW_SPADE1_IMG_PATH,
  HIGHANDLOW_SPADE2_IMG_PATH,
  HIGHANDLOW_SPADE3_IMG_PATH,
  HIGHANDLOW_SPADE4_IMG_PATH,
  HIGHANDLOW_SPADE5_IMG_PATH,
  HIGHANDLOW_SPADE6_IMG_PATH,
  HIGHANDLOW_SPADE7_IMG_PATH,
  HIGHANDLOW_SPADE8_IMG_PATH,
  HIGHANDLOW_SPADE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg) {
  m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg) {
  m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg) {
  m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse() {
  m_flag_btnA_is_pressed = false;
  m_flag_btnB_is_pressed = false;
  m_flag_btnC_is_pressed = false;
}

State AppControl::getState() {
  return m_state;
}

void AppControl::setState(State state) {
  m_state = state;
}

Action AppControl::getAction() {
  return m_action;
}

void AppControl::setAction(Action action) {
  m_action = action;
}

void AppControl::setStateMachine(State state, Action action) {
  setState(state);
  setAction(action);
}

FocusState AppControl::getFocusState() {
  return m_focus_state;
}

void AppControl::setFocusState(FocusState fs) {
  m_focus_state = fs;
}

void AppControl::displayTitleInit() {
  mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH, TITLE_X_CRD, TITLE_Y_CRD);
}

void AppControl::displayMenuInit() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
  mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
  mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
  mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, MENU_UP_X_CRD, MENU_UP_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, MENU_DECIDE_X_CRD, MENU_DECIDE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, MENU_DOWN_X_CRD, MENU_DOWN_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state) {
  switch (current_state) {
    case MENU_WBGT:
      mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
      break;

    case MENU_MUSIC:
      mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
      break;

    case MENU_MEASURE:
      mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
      break;

    case MENU_DATE:
      mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
      break;
  }

  switch (next_state) {
    case MENU_WBGT:
      mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
      break;

    case MENU_MUSIC:
      mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
      break;

    case MENU_MEASURE:
      mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
      break;

    case MENU_DATE:
      mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
      break;
  }
}

void AppControl::displayWBGTInit() {
  mwbgt.init();
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_X_CRD, WBGT_TEMPERATURE_Y_CRD);
  mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_X_CRD, WBGT_HUMIDITY_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, WBGT_BACK_X_CRD, WBGT_BACK_Y_CRD);
  mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_X_CRD, WBGT_DEGREE_Y_CRD);
  mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_X_CRD, WBGT_PERCENT_Y_CRD);
}

void AppControl::displayTempHumiIndex() {
  double temp;
  double humi;
  WbgtIndex index;
  mwbgt.getWBGT(&temp,&humi,&index);
  switch (index)
  {
  case SAFE:
    mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
    break;

  case ATTENTION:
    mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
    break;

  case ALERT:
    mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
    break;

  case HIGH_ALERT:
    mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
    break;

  case DANGER:
    mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
    break;

  default:
    break;
  }

  //温度の数値表示
  mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);
  int digit_remainder_t = (int)(temp*10);
  if(digit_remainder_t<100){
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEFILLWHITE_IMG_PATH, WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);
  }else{
    int digit2_t = digit_remainder_t / 100;
    digit_remainder_t = digit_remainder_t % 100;
    mlcd.displayJpgImageCoordinate(g_str_orange[digit2_t], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);
  }
    int digit1_t = digit_remainder_t / 10;
    digit_remainder_t = digit_remainder_t % 10;
    mlcd.displayJpgImageCoordinate(g_str_orange[digit1_t], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD);
    int decimal1_t = digit_remainder_t / 1;
    mlcd.displayJpgImageCoordinate(g_str_orange[decimal1_t], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);
  
  //湿度の数値表示
  mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);
  int digit_remainder_h = (int)(humi*10);
  if(digit_remainder_h<100){
    mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);
  }else{
    int digit2_h = digit_remainder_h / 100;
    digit_remainder_h = digit_remainder_h % 100;
    mlcd.displayJpgImageCoordinate(g_str_blue[digit2_h], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);
  }
    int digit1_h = digit_remainder_h / 10;
    digit_remainder_h = digit_remainder_h % 10;
    mlcd.displayJpgImageCoordinate(g_str_blue[digit1_h], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD);
    int decimal1_h = digit_remainder_h / 1;
    mlcd.displayJpgImageCoordinate(g_str_blue[decimal1_h], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);
}

void AppControl::displayMusicInit() {
  displayMusicStop();
  displayMusicTitle();
}

void AppControl::displayMusicStop() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, MUSIC_NOTICE_X_CRD, MUSIC_NOTICE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, MUSIC_PLAY_X_CRD, MUSIC_PLAY_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, MUSIC_BACK_X_CRD, MUSIC_BACK_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, MUSIC_NEXT_X_CRD, MUSIC_NEXT_Y_CRD);
}

void AppControl::displayMusicTitle() {
  mlcd.displayText("               ", MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
  mlcd.displayText(mmplay.getTitle(), MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
}

void AppControl::displayNextMusic() {
  mmplay.selectNextMusic();
  displayMusicTitle();
}

void AppControl::displayMusicPlay() {
  displayMusicTitle();
  mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, MUSIC_NOTICE_X_CRD, MUSIC_NOTICE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, MUSIC_STOP_X_CRD, MUSIC_STOP_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_FILLWHITE_IMG_PATH, MUSIC_BACK_X_CRD, MUSIC_BACK_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_FILLWHITE_IMG_PATH, MUSIC_NEXT_X_CRD, MUSIC_NEXT_Y_CRD);
}

void AppControl::displayMeasureInit() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, MEASURE_NOTICE_X_CRD, MEASURE_NOTICE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, MEASURE_BACK_X_CRD, MEASURE_BACK_Y_CRD);
  mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, MEASURE_CM_X_CRD, MEASURE_CM_Y_CRD);
}

void AppControl::displayMeasureDistance() {
  if (2.0 <= mmdist.getDistance() && mmdist.getDistance() <= 450.0) {
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);
    int digit_remainder = (int)(mmdist.getDistance()*100);
    if(digit_remainder<10000){
      mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
    }else{
      int digit3 = digit_remainder / 10000;
      digit_remainder = digit_remainder % 10000;
      mlcd.displayJpgImageCoordinate(g_str_blue[digit3], MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
    }
    if(digit_remainder<1000){
      mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
    }else{
      int digit2 = digit_remainder / 1000;
      digit_remainder = digit_remainder % 1000;
      mlcd.displayJpgImageCoordinate(g_str_blue[digit2], MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
    }
    int digit1 = digit_remainder / 100;
    digit_remainder = digit_remainder % 100;
    mlcd.displayJpgImageCoordinate(g_str_blue[digit1], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD);
    int decimal1 = digit_remainder / 10;
    mlcd.displayJpgImageCoordinate(g_str_blue[decimal1], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);
  }
}

void AppControl::displayDateInit() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, DATE_NOTICE_X_CRD, DATE_NOTICE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATE_BACK_X_CRD, DATE_BACK_Y_CRD);
}

void AppControl::displayDateUpdate() {
  mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);
  mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);
}

void AppControl::displayHighAndLowInit() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_TITLE_IMG_PATH, HIGHANDLOW_TITLE_X_CRD, HIGHANDLOW_TITLE_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_START_IMG_PATH, HIGHANDLOW_START_X_CRD, HIGHANDLOW_START_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, HIGHANDLOW_BACK_X_CRD, HIGHANDLOW_BACK_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_RECORD_IMG_PATH, HIGHANDLOW_RECORD_X_CRD, HIGHANDLOW_RECORD_Y_CRD);
}

void AppControl::displayHighAndLowBattle() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  highandlow.leftCard();
  highandlow.rightCard();
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_HIGHANDLOW_IMG_PATH, HIGHANDLOW_HIGHANDLOW_X_CRD, HIGHANDLOW_HIGHANDLOW_Y_CRD);
  mlcd.displayJpgImageCoordinate(g_str_heart[highandlow.getLeftCard()], HIGHANDLOW_LEFTCARD_X_CRD, HIGHANDLOW_LEFTCARD_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_BACK_IMG_PATH, HIGHANDLOW_RIGHTCARD_X_CRD, HIGHANDLOW_RIGHTCARD_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_HIGH_IMG_PATH, HIGHANDLOW_HIGH_X_CRD, HIGHANDLOW_HIGH_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_LOW_IMG_PATH, HIGHANDLOW_LOW_X_CRD, HIGHANDLOW_LOW_Y_CRD);
}

void AppControl::displayHighAndLowResult() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  highandlow.gameJudgement();
  if(highandlow.getWinJudgement()){
    mlcd.displayJpgImageCoordinate(HIGHANDLOW_WIN_IMG_PATH, HIGHANDLOW_WIN_X_CRD, HIGHANDLOW_WIN_Y_CRD);
  }else{
    mlcd.displayJpgImageCoordinate(HIGHANDLOW_LOSE_IMG_PATH, HIGHANDLOW_LOSE_X_CRD, HIGHANDLOW_LOSE_Y_CRD);
  }
  mlcd.displayJpgImageCoordinate(g_str_heart[highandlow.getLeftCard()], HIGHANDLOW_LEFTCARD_X_CRD, HIGHANDLOW_LEFTCARD_Y_CRD);
  mlcd.displayJpgImageCoordinate(g_str_spade[highandlow.getRightCard()], HIGHANDLOW_RIGHTCARD_X_CRD, HIGHANDLOW_RIGHTCARD_Y_CRD);
  mlcd.displayJpgImageCoordinate(HIGHANDLOW_ONEMORE_IMG_PATH, HIGHANDLOW_ONEMORE_X_CRD, HIGHANDLOW_ONEMORE_Y_CRD);
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, HIGHANDLOW_BACK_X_CRD, HIGHANDLOW_BACK_Y_CRD);
}

void AppControl::displayHighAndLowRecord() {
  mlcd.clearDisplay();
  mlcd.fillBackgroundWhite();
  mlcd.displayText("1234567", HIGHANDLOW_RECORD_TEXT_X_CRD, HIGHANDLOW_RECORD_TEXT_Y_CRD); 
  mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, HIGHANDLOW_BACK_X_CRD, HIGHANDLOW_BACK_Y_CRD); 
}

void AppControl::controlApplication() {
  bool music_stop_state = false;
  int high_and_low_title_state=2;
  mmplay.init();

  while (1) {

    switch (getState()) {
      case TITLE:
        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
            displayTitleInit();
            setStateMachine(TITLE, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed) {
              setStateMachine(TITLE, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(MENU, ENTRY);
            break;

          default:
            break;
        }

        break;

      case MENU:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayMenuInit();
            setFocusState(MENU_WBGT);
            focusChangeImg(getFocusState(), getFocusState());
            setStateMachine(MENU, DO);
            break;

        static int up_count;
        static int down_count;
          case DO:
          if(up_count>2){
            up_count=0;
            down_count=0;
          }
          if(down_count>2){
            up_count=0;
            down_count=0;
          }
          if(up_count==1){
            if(down_count==1){
            up_count=0;
            down_count=0;
            }
          }
          if(down_count==1){
            if(up_count==1){
            up_count=0;
            down_count=0;
            }
          }
          if(up_count==0 && down_count>=1){
            up_count=0;
            down_count=0;
          }
          Serial.println(getState());
            if (getFocusState() == MENU_WBGT) {
              if (m_flag_btnA_is_pressed) {
                up_count++;
                focusChangeImg(MENU_WBGT, MENU_DATE);
                setFocusState(MENU_DATE);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnC_is_pressed) {
                down_count++;
                focusChangeImg(MENU_WBGT, MENU_MUSIC);
                setFocusState(MENU_MUSIC);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnB_is_pressed) {
                if(up_count == 2){
                  if(down_count == 2){
                    setFocusState(MENU_HIGH_AND_LOW);
                  }
                }
                setStateMachine(MENU, EXIT);
                setBtnAllFlgFalse();
              }
            }
            if (getFocusState() == MENU_MUSIC) {
              if (m_flag_btnA_is_pressed) {
                up_count++;
                focusChangeImg(MENU_MUSIC, MENU_WBGT);
                setFocusState(MENU_WBGT);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnC_is_pressed) {
                down_count++;
                focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                setFocusState(MENU_MEASURE);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnB_is_pressed) {
                if(up_count == 2){
                  if(down_count == 2){
                    setFocusState(MENU_HIGH_AND_LOW);
                  }
                }
                setStateMachine(MENU, EXIT);
                setBtnAllFlgFalse();
              }
            }
            if (getFocusState() == MENU_MEASURE) {
              if (m_flag_btnA_is_pressed) {
                up_count++;
                focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                setFocusState(MENU_MUSIC);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnC_is_pressed) {
                down_count++;
                focusChangeImg(MENU_MEASURE, MENU_DATE);
                setFocusState(MENU_DATE);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnB_is_pressed) {
                if(up_count == 2){
                  if(down_count == 2){
                    setFocusState(MENU_HIGH_AND_LOW);
                  }
                }
                setStateMachine(MENU, EXIT);
                setBtnAllFlgFalse();
              }
            }
            if (getFocusState() == MENU_DATE) {
              if (m_flag_btnA_is_pressed) {
                up_count++;
                focusChangeImg(MENU_DATE, MENU_MEASURE);
                setFocusState(MENU_MEASURE);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnC_is_pressed) {
                down_count++;
                focusChangeImg(MENU_DATE, MENU_WBGT);
                setFocusState(MENU_WBGT);
                setBtnAllFlgFalse();
              }
              if (m_flag_btnB_is_pressed) {
                if(up_count == 2){
                  if(down_count == 2){
                    setFocusState(MENU_HIGH_AND_LOW);
                  }
                }
                setStateMachine(MENU, EXIT);
                setBtnAllFlgFalse();
              }
            }

            break;

          case EXIT:
          Serial.println(getState());
            up_count=0;
            down_count=0;            
            switch (getFocusState()) {
              case MENU_WBGT:
                setStateMachine(WBGT, ENTRY);
                break;
              case MENU_MUSIC:
                setStateMachine(MUSIC_STOP, ENTRY);
                break;
              case MENU_MEASURE:
                setStateMachine(MEASURE, ENTRY);
                break;
              case MENU_DATE:
                setStateMachine(DATE, ENTRY);
                break;
              case MENU_HIGH_AND_LOW:
                setStateMachine(HIGH_AND_LOW_TITLE, ENTRY);
                break;
            }
        }

        break;

      case WBGT:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayWBGTInit();
            setStateMachine(WBGT, DO);
            break;

          case DO:
          Serial.println(getState());
            displayTempHumiIndex();
            delay(100);
            if (m_flag_btnB_is_pressed) {
              setStateMachine(WBGT, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(MENU, ENTRY);
            break;

          default:
            break;
        }

        break;

      case MUSIC_STOP:
        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayMusicInit();
            setStateMachine(MUSIC_STOP, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnA_is_pressed) {
              music_stop_state = true;
              setStateMachine(MUSIC_STOP, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnB_is_pressed) {
              music_stop_state = false;
              setStateMachine(MUSIC_STOP, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnC_is_pressed) {
              displayNextMusic();
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            if (music_stop_state == true) {
              music_stop_state = false;
              setStateMachine(MUSIC_PLAY, ENTRY);
            } else {
              setStateMachine(MENU, ENTRY);
            }

            break;

          default:
            break;
        }

        break;

      case MUSIC_PLAY:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayMusicPlay();
            mmplay.prepareMP3();
            setStateMachine(MUSIC_PLAY, DO);
            break;

          case DO:
          Serial.println(getState());
            if ( !(mmplay.playMP3()) || m_flag_btnA_is_pressed ) {
              setStateMachine(MUSIC_PLAY, EXIT);
              setBtnAllFlgFalse();
            }

            break;

          case EXIT:
          Serial.println(getState());
            mmplay.stopMP3();
            setStateMachine(MUSIC_STOP, ENTRY);
            break;

          default:
            break;
        }

        break;

      case MEASURE:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayMeasureInit();
            setStateMachine(MEASURE, DO);
            break;

          case DO:
          Serial.println(getState());
            displayMeasureDistance();
            delay(250);
            if (m_flag_btnB_is_pressed) {
              setStateMachine(MEASURE, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(MENU, ENTRY);
            break;

          default:
            break;
        }

        break;

      case DATE:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayDateInit();
            setStateMachine(DATE, DO);
            break;

          case DO:
          Serial.println(getState());
            displayDateUpdate();
            delay(100);

            if (m_flag_btnB_is_pressed) {
              setStateMachine(DATE, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(MENU, ENTRY);
            break;

          default:
            break;
        }
      
        break;

      case HIGH_AND_LOW_TITLE:
        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayHighAndLowInit();
            setStateMachine(HIGH_AND_LOW_TITLE, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnA_is_pressed) {
              high_and_low_title_state=1;
              setStateMachine(HIGH_AND_LOW_TITLE, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnB_is_pressed) {
              high_and_low_title_state=2;
              setStateMachine(HIGH_AND_LOW_TITLE, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnC_is_pressed) {
              high_and_low_title_state=3;
              setStateMachine(HIGH_AND_LOW_TITLE, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            switch(high_and_low_title_state){
              case 1:
                high_and_low_title_state=2;
                setStateMachine(HIGH_AND_LOW_BATTLE, ENTRY);
              break;

              case 2:
                high_and_low_title_state=2;
                setStateMachine(MENU, ENTRY);
              break;

              case 3:
                high_and_low_title_state=2;
                setStateMachine(HIGH_AND_LOW_RECORD, ENTRY);
              break;

              default:
              break;
            }

            break;

          default:
            break;
        }

        break;

      case HIGH_AND_LOW_RECORD:

        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayHighAndLowRecord();
            setStateMachine(HIGH_AND_LOW_RECORD, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnB_is_pressed) {
              setStateMachine(HIGH_AND_LOW_RECORD, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(HIGH_AND_LOW_TITLE, ENTRY);
            break;

          default:
            break;
        }
      
        break;
      
      case HIGH_AND_LOW_BATTLE:
        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayHighAndLowBattle();
            setStateMachine(HIGH_AND_LOW_BATTLE, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnA_is_pressed) {
              highandlow.setSelect(BIG);
              setStateMachine(HIGH_AND_LOW_BATTLE, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnC_is_pressed) {
              highandlow.setSelect(SMALL);
              setStateMachine(HIGH_AND_LOW_BATTLE, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            setStateMachine(HIGH_AND_LOW_RESULT, ENTRY);
            break;

          default:
            break;
        }
      
        break;
      
      case HIGH_AND_LOW_RESULT:
        switch (getAction()) {
          case ENTRY:
          Serial.println(getState());
            displayHighAndLowResult();
            setStateMachine(HIGH_AND_LOW_RESULT, DO);
            break;

          case DO:
          Serial.println(getState());
            if (m_flag_btnA_is_pressed) {
              highandlow.setContinue(ONEMORE);
              setStateMachine(HIGH_AND_LOW_RESULT, EXIT);
              setBtnAllFlgFalse();
            }
            if (m_flag_btnB_is_pressed) {
              highandlow.setContinue(BACK);
              setStateMachine(HIGH_AND_LOW_RESULT, EXIT);
              setBtnAllFlgFalse();
            }
            break;

          case EXIT:
          Serial.println(getState());
            if(highandlow.getContinue()==ONEMORE){
              highandlow.setContinue(BACK);
              setStateMachine(HIGH_AND_LOW_BATTLE, ENTRY);
            }else{
              setStateMachine(HIGH_AND_LOW_TITLE, ENTRY);
            }
            
            break;

          default:
            break;
        }
      
        break;

      default:
        break;
    }
  }
}
