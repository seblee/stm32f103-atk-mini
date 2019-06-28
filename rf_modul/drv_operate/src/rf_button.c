/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   BUTTON配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#include "rf_button.h"
#include "rf_delay.h"

#define KEY_CHECK_BASE 0x01 //mask code
#define KEY_NUM 1           //1 KEY

uint8_t Key_Down_Trg = 0;          //按鍵單次狀態
uint8_t Key_Up_Trg = 0;            //按鍵短按 放開
uint8_t Key_Count = 0;             //按鍵長按狀態 按下/放開狀態
uint8_t Key_Restain = 0;           //按鍵按捺狀態
uint8_t Key_Restain_Trg = 0;       //按鍵按捺狀態
uint8_t Key_Short_Restain = 0;     //按鍵按捺狀態
uint8_t Key_Short_Restain_Trg = 0; //按鍵按捺狀態

static void Eland_Key_Long_Press_State(void);

/**
  * @brief :按键初始化
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_button_init(void)
{
    rt_pin_mode(BUTTON_PIN, PIN_MODE_INPUT_PULLDOWN);
}
/**
  * @brief :按键查询
  * @param :无
  * @note  :无
  * @retval:
  *	        0:按键没有按下
  *	        1:检测到按键动作
  */
uint8_t rf_button_check(void)
{
    static uint8_t KeyValue_last = 0;
    uint8_t KeyValue_present = 0, ReadData = 0;

    KeyValue_present = (PIN_HIGH == rt_pin_read(BUTTON_PIN)) ? 1 : 0; //key当前值
    if (KeyValue_present == KeyValue_last)                            //去抖20ms
    {
        ReadData = KeyValue_present;
    }
     

    Key_Down_Trg = ReadData & (ReadData ^ Key_Count);
    Key_Count = ReadData;

    KeyValue_last = KeyValue_present;
    Eland_Key_Long_Press_State();
    return Key_Down_Trg;
}
/**
 ****************************************************************************
 * @Function : void Eland_Key_Long_Press_State(void)
 * @File     : key.c
 * @Program  : none
 * @Created  : 2017/11/2 by seblee
 * @Brief    : check long press state 20ms 訪問一次
 * @Version  : V1.0
**/
static void Eland_Key_Long_Press_State(void)
{
    static uint8_t KEY_Timer[KEY_NUM];
    uint8_t i;
    static uint16_t Key_Restain_Count = 0;
    static uint16_t Key_Short_Restain_Count = 0;
    uint8_t long_press_time_tem;
    for (i = 0; i < KEY_NUM; i++)
    {
        if (i == 8)
            long_press_time_tem = ALARM_OFF_LONG_PRESS_TIMES;
        else
            long_press_time_tem = LONG_PRESS_TIMES;
        if (Key_Count & (1 << i))
        {
            if (KEY_Timer[i] < long_press_time_tem)
                KEY_Timer[i]++;
            else
                Key_Restain |= (1 << i);

            if (KEY_Timer[i] > SHSORT_RESTAIN_TIMES)
                Key_Short_Restain |= (1 << i);
        }
        else
        {
            if ((KEY_Timer[i] > 0) && (KEY_Timer[i] < long_press_time_tem)) // short press
                Key_Up_Trg |= (1 << i);
            else
                Key_Up_Trg &= (~(1 << i));
            KEY_Timer[i] = 0;
            Key_Restain &= (~(1 << i));
            Key_Short_Restain &= (~(1 << i));
        }
    }
    Key_Restain_Trg = Key_Restain & (Key_Restain ^ Key_Restain_Count);
    Key_Restain_Count = Key_Restain;
    Key_Short_Restain_Trg = Key_Short_Restain & (Key_Short_Restain ^ Key_Short_Restain_Count);
    Key_Short_Restain_Count = Key_Short_Restain;
}
