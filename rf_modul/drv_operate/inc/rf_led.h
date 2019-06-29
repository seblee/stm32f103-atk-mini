/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   LED配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#ifndef __RF_LED_H__
#define __RF_LED_H__

#include <rtthread.h>
#include <rthw.h>
#include "board.h"

//LED硬件定义
#define LED_RED_PIN GET_PIN(A, 8)
#define LED_GREEN_PIN GET_PIN(D, 2)

#define LED_RED_GPIO_PORT GPIOA
#define LED_RED_GPIO_PIN GPIO_PIN_8

#define LED_GREEN_GPIO_PORT GPIOD
#define LED_GREEN_GPIO_PIN GPIO_PIN_2

/** LED定义 */
typedef enum LedPort
{
  LED_RED = 0, //红色LED
  LED_GREEN    //绿色LED
} LedPortType;
typedef enum
{
  LED_SEND ,    //SEND FLASH
  LED_RECEIVE, //RECEIVE FLASH
} LedCmdType;

extern rt_mq_t led_mq;

void rf_led_init(void);
void rf_led_on(LedPortType LedPort);
void rf_led_off(LedPortType LedPort);
void rf_led_flashing(LedPortType LedPort);

//红色LED操作函数
#define led_red_on() rf_led_on(LED_RED)
#define led_red_off() rf_led_off(LED_RED)
#define led_red_flashing() rf_led_flashing(LED_RED)
//蓝色LED操作函数
#define led_green_on() rf_led_on(LED_GREEN)
#define led_green_off() rf_led_off(LED_GREEN)
#define led_green_flashing() rf_led_flashing(LED_GREEN)

void rf_led(void *parameter);
void operate_led(LedCmdType cmd);

#endif
