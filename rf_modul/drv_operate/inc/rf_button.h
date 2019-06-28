/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   BUTTON配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#ifndef __RF_BUTTON_H__
#define __RF_BUTTON_H__

#include <rtthread.h>
#include <rthw.h>
#include "board.h"

#define BUTTON_PIN GET_PIN(A, 0)

#define LONG_PRESS_TIMES 250           //250 × 20ms = 5s
#define ALARM_OFF_LONG_PRESS_TIMES 200 //200 × 20ms = 4s
#define SHSORT_RESTAIN_TIMES 50        //50 × 20ms = 1s
#define SW_LIGHT_TIMES 250             //250 × 20ms = 5s

/** 按键状态定义 */
enum
{
    BUTOTN_UP = 0,    //按键未按下
    BUTOTN_PRESS_DOWN //按键按下
};

void rf_button_init(void);
uint8_t rf_button_check(void);

#endif
