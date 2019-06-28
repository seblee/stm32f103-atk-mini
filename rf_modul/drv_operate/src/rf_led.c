/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   LED配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#include "rf_led.h"

rt_mq_t led_mq = RT_NULL;

/**
  * @brief :LED初始化
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_led_init(void)
{
    rt_pin_mode(LED_RED_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_GREEN_PIN, PIN_MODE_OUTPUT);

    led_mq = rt_mq_create("led_mq", 4, 10, RT_IPC_FLAG_FIFO);
    if (led_mq != RT_NULL)
    {
        rt_kprintf("CREAT message queue failed.\n");
        return -1;
    }

    rt_thread_t rf_thread;
    rf_thread = rt_thread_create("rf_led", rf_led, RT_NULL,
                                 256, 30, 30);
    RT_ASSERT(rf_thread != RT_NULL);
    if (rf_thread != RT_NULL)
        rt_thread_startup(rf_thread);
}

/**
  * @brief :LED亮
  * @param :
  *			@LedPort:LED选择，红色或蓝色
  * @note  :无
  * @retval:无
  */
void rf_led_on(LedPortType LedPort)
{
    if (LED_RED == LedPort) //LED_RED
    {
        rt_pin_write(LED_RED_PIN, PIN_LOW);
    }
    else //LED_GREEN
    {
        rt_pin_write(LED_GREEN_PIN, PIN_LOW);
    }
}

/**
  * @brief :LED灭
  * @param :
  *			@LedPort:LED选择，红色或蓝色
  * @note  :无
  * @retval:无
  */
void rf_led_off(LedPortType LedPort)
{
    if (LED_RED == LedPort) //LED_RED
    {
        rt_pin_write(LED_RED_PIN, PIN_HIGH); //红色LED引脚置高，红色LED灭
    }
    else //LED_GREEN
    {
        rt_pin_write(LED_GREEN_PIN, PIN_HIGH); //蓝色LED引脚置高，蓝色LED灭
    }
}

/**
  * @brief :LED闪烁
  * @param :
  *			@LedPort:LED选择，红色或蓝色
  * @note  :无
  * @retval:无
  */
void rf_led_flashing(LedPortType LedPort)
{
    if (LED_RED == LedPort)
    {
        HAL_GPIO_TogglePin(LED_RED_GPIO_PORT, LED_RED_GPIO_PIN);
    }
    else
    {
        HAL_GPIO_TogglePin(LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN);
    }
}
void rf_app(void *parameter)
{
    while (1)
    {
    }
}