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
#include "protocol.h"

/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(A, 8)

static void start(void);
static void stop(void);
static unsigned int s = 0;

_pid pid = 
{
    .target_val = 40,
    .Kp = 0.1,
    .Ki = 0.2,
    .Kd = 0.3,
    .ducy_ms = 100,
    .start = start,
    .stop = stop,
};




static rt_timer_t timer1;
static int val = 0;

static void timeout1(void *parameter)
{
    static int val = 0;
    
    while(1)
    {
        set_computer_value(SEND_FACT_CMD, CURVES_CH1, &val, 1);
        
        s = 1;
        val += 1;
    }
}


static void start(void)
{

    timer1 = rt_timer_create("timer1", timeout1,
                             RT_NULL, 20,
                             RT_TIMER_FLAG_PERIODIC);

    if (timer1 != RT_NULL) rt_timer_start(timer1);
}

static void stop(void)
{
    if(s == 0)
        return;
    
    rt_timer_delete(timer1);
}

int main(void)
{
    
    protocol_init();
    
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        receiving_process();
        #if 0
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
#endif
        
        
    }

    return RT_EOK;
}



