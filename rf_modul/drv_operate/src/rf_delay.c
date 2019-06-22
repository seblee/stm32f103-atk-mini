/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   DELAY配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#include "rf_delay.h"

/**
  * @brief :延时初始化
  * @param :无
  * @note  :定时器默认初始化成us级计数
  * @retval:无
  */

/**
  * @brief :延时(us)
  * @param :
*			@Us:延时的us数
  * @note  :不超过65535
  * @retval:无
  */
void rf_delay_us(uint16_t Us)
{
    rt_hw_us_delay(Us);
}

/**
  * @brief :延时(ms)
  * @param :
  *			@Ms:延时的Ms数
  * @note  :不超过65
  * @retval:无
  */
void rf_delay_ms(uint8_t Ms)
{
    rt_thread_mdelay(Ms);
}

/**
  * @brief :延时(500Ms)
  * @param :
*			@Ms:延时的500Ms倍数
  * @note  :不超过255
  * @retval:无
  */
void rf_delay_500Ms(uint8_t Ms_500)
{
    while (Ms_500--)
    {
        rt_thread_mdelay(500); //  500ms
    }
}

/**
  * @brief :自由延时
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_delay_free(uint32_t Delay_Time)
{
    while (Delay_Time--)
    {
    }
}
