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
#include <stdio.h>

float pwm_to_speed(float pwm)
{
    return pwm/500;
}

/*pid*/
typedef struct
{
     float target_val;               //目标值
     float actual_val;               //实际值
     float err;                              //定义偏差值
     float err_last;                         //定义上一个偏差值
     float Kp,Ki,Kd;                         //定义比例、积分、微分系数
     float integral;                         //定义积分值
}_pid;

static _pid pid;
 
  /**
 * @brief  PID参数初始化
 *   @note   无
 * @retval 无
 */
static int PID_param_init()
{
     /* 初始化参数 */
     pid.target_val=50;
     pid.actual_val=0.0;
     pid.err=0.0;
     pid.err_last=0.0;
     pid.integral=0.0;
     pid.Kp = 0.5;
     pid.Ki = 0.0;
     pid.Kd = 0.0;
};

INIT_BOARD_EXPORT(PID_param_init);
 
 /**
  * @brief  PID算法实现
  * @param  val              实际值
  * @note    无
  * @retval 通过PID计算后的输出
  */
float PID_realize(float temp_val)
{
    float pwm;
    
     /*目标值只在这里参与计算，计算目标值与实际值的误差*/
    pid.err=pid.target_val-temp_val;
     /*误差累积*/
    pid.integral+=pid.err;
     /*PID算法实现*/
    pwm=pid.Kp*pid.err;/*   +pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);*/
     /*误差传递*/
    pid.err_last=pid.err;
     /*返回的值是经过pid运算以后的值*/
    return pwm;
}

 /**
 * @brief  定时器周期调用函数
 * @param  无
     *       @note   无
 * @retval 无
 */
static int pid_fun(int argc, char *argv[])
{
    
    char str[32];
    float pwm = 1;
   
    for (unsigned int i = 0; i< 500000; i ++)
    {
        //float speed = pwm_to_speed(pwm);
        
        pwm=PID_realize(pwm);
        
        sprintf(str, "%f\n", pwm);
        
        rt_kprintf(str);
    }

}

MSH_CMD_EXPORT(pid_fun ,test pid);
