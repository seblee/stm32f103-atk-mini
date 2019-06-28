/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   主函数C文件
  ******************************************************************************
  * @attention
  *
  * 官网    :   http://www.ashining.com
  * 淘宝    :   https://shop105912646.taobao.com
  * 阿里巴巴:   https://cdzeyao.1688.com
  ******************************************************************************
  */

#include "rf_app.h"

#define DBG_TAG "rf.app"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

const char *g_Ashining = "**ashining##";
uint8_t g_UartRxBuffer[100] = {0};
uint8_t g_RF24L01RxBuffer[256] = {0};
rt_sem_t rf_sem = RT_NULL;
/**
  * @brief :主函数 
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_app(void *parameter)
{
    uint8_t i = 0;
    static rt_err_t result;
    LOG_E("rf_app");
    /* 创建一个动态信号量，初始值是 0 */
    rf_sem = rt_sem_create("rf_sem", 0, RT_IPC_FLAG_FIFO);
    if (rf_sem == RT_NULL)
    {
        LOG_E("create dynamic semaphore failed.");
    }
    else
    {
        LOG_D("create rf_sem done");
    }
    //LED初始化
    rf_led_init();
    //按键初始化
    rf_button_init();
    //SPI初始化
    rf_spi_init();
    //CC1101初始化
    CC1101_Init();

    for (i = 0; i < 6; i++)
    {
        led_red_flashing();
        led_green_flashing();
        rf_delay_ms(250);
    }
    CC1101_Set_RX_Mode();
    g_Modul_state.radioMode = RX_MODE;
    while (1)
    {
        result = rt_sem_take(rf_sem, 20);
        if (result != RT_EOK)
        {
            uint8_t key_value;
            key_value = rf_button_check();
            if ((BUTOTN_PRESS_DOWN == key_value) && (0 != CC1101_GET_GDO0_STATUS()))
            {
                //状态显示清零
                led_red_off();
                for (i = 0; i < 6; i++)
                {
                    led_red_flashing();
                    rf_delay_ms(250);
                }
                //************************************* 发送 **********************************************//
                CC1101_Tx_Packet((uint8_t *)g_Ashining, 12, ADDRESS_CHECK); //模式1发送固定字符,1S一包
                led_red_flashing();
                rf_delay_ms(250);
                led_red_off();
            }
        }
        else /************************************* 接收 **********************************************/
        {
            CC1101_Status_t statue;
             statue = CC1101_GetRxStatus();
            LOG_I("statue:0x%02x", statue.BYTE);
            if (0 == CC1101_GET_GDO0_STATUS()) //正在接收状态
            {
                LOG_I("Rx_Packet");
                i = CC1101_Rx_Packet(g_RF24L01RxBuffer); //接收字节
                if (0 != i)
                {
                    led_green_flashing();
                    LOG_I("%s", g_RF24L01RxBuffer); //输出接收到的字节
                    rt_memset(g_RF24L01RxBuffer, 0, sizeof(g_RF24L01RxBuffer));
                }
            }
        }
    }
}

/**
************************************************************************************************************************
 * @Function    :        
 * @author      :   xiaowine@cee0.com
 * @brief       :     
 * @param       :     
 * @Return      :   None
 * @?μ?÷        :        
************************************************************************************************************************
*/
void gdo0_irq(void *args)
{
    if (g_Modul_state.radioMode == RX_MODE)
        rt_sem_release(rf_sem);
}
