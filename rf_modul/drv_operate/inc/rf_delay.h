/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   DELAY配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#ifndef __RF_DELAY_H__
#define __RF_DELAY_H__

#include <rtthread.h>
#include <rthw.h>

/** 采用定时器做精确延时 */

void rf_delay_us(uint16_t Us);
void rf_delay_ms(uint8_t Ms);
void rf_delay_500Ms(uint8_t Ms_500);
void rf_delay_free(uint32_t Delay_Time);

#endif
