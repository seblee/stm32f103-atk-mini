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
  *			0:按键没有按下
  *			1:检测到按键动作
  */
uint8_t rf_button_check(void)
{
    if (PIN_HIGH == rt_pin_read(BUTTON_PIN)) //检测按键输入状态
    {
        rf_delay_ms(50); //消抖
        if (PIN_HIGH == rt_pin_read(BUTTON_PIN))
        {
            return 1; //按键按下，返回按键状态
        }
    }

    return 0;
}
