/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB1 */
//#define LED0_PIN    GET_PIN(A, 8)
void rf_app(void *parameter);
int main(void)
{
      /* set LED0 pin mode to output */
    //rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    /**
     * init thread 
     */
    rt_thread_t rf_thread;
    rf_thread = rt_thread_create("rf_app", rf_app, RT_NULL,
                                 0x1000, 20, 5);
    RT_ASSERT(rf_thread != RT_NULL);
    if (rf_thread != RT_NULL)
        rt_thread_startup(rf_thread);

 

    return RT_EOK;
}
