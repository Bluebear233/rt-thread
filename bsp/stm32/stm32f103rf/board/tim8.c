#include "main.h"
#include "board.h"
/* USER CODE BEGIN Includes */
#include <drv_common.h>
/* USER CODE END Includes */
#include <stdio.h>

static TIM_HandleTypeDef htim2;

#define OC_CNT_MAX 1000 - 1 

static int tim8_init(void)
{
    // GPIO INIT
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        __HAL_RCC_TIM2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM2 GPIO Configuration
        PA0-WKUP     ------> TIM2_CH1
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* TIM2 interrupt Init */
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
    
    {
        /* USER CODE BEGIN TIM2_Init 0 */

        /* USER CODE END TIM2_Init 0 */

        TIM_ClockConfigTypeDef sClockSourceConfig = {0};
        TIM_SlaveConfigTypeDef sSlaveConfig = {0};
        TIM_MasterConfigTypeDef sMasterConfig = {0};
        TIM_IC_InitTypeDef sConfigIC = {0};

        /* USER CODE BEGIN TIM2_Init 1 */

        /* USER CODE END TIM2_Init 1 */
        htim2.Instance = TIM2;
        htim2.Init.Prescaler = 36-1;
        htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim2.Init.Period = 65535;
        htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
        if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
        {
            Error_Handler();
        }
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
        {
            Error_Handler();
        }
        sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
        sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
        sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
        sSlaveConfig.TriggerFilter = 0;
        if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
        {
            Error_Handler();
        }
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
        {
            Error_Handler();
        }
        sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
        sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
        sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
        sConfigIC.ICFilter = 0;
        if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
        {
            Error_Handler();
        }
        sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
        sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
        if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
        {
            Error_Handler();
        }
        /* USER CODE BEGIN TIM2_Init 2 */

        /* USER CODE END TIM2_Init 2 */

        
        /* 使能捕获/比较 2 中断请求 */
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
        //HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2); 
        
        
    }
    
    // __HAL_TIM_ENABLE(&htim2);
    
    return 0;
}
INIT_BOARD_EXPORT(tim8_init);

/* 定时器超时回调函数 */
static int tim2(int argc, char *argv[])
{
    //tim8_init();
    TIM2->CNT = 0;
    //__HAL_TIM_ENABLE(&htim2);
    //__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(tim2 ,test PWM Duty cycle);

void TIM2_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_CC1) != RESET) {
        /* 清除TIM2更新中断标志 */

        __HAL_TIM_DISABLE(&htim2);
        __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC1);
 
        rt_kprintf("chanle1:%d", TIM2->CCR1);
        
        
        
        // rt_kprintf("chanle2:%d", TIM2->CCR2);
        //__HAL_RCC_TIM2_CLK_DISABLE();
        
    }
}
