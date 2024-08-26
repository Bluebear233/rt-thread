#include "main.h"
#include "board.h"
/* USER CODE BEGIN Includes */
#include <drv_common.h>
/* USER CODE END Includes */
#include <stdio.h>

static TIM_HandleTypeDef htim1;

#define OC_CNT_MAX 1000 - 1 

static int tim1_init(void)
{
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO INIT
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        
    __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM1 GPIO Configuration
        PA7     ------> TIM1_CH1N
        PA8     ------> TIM1_CH1
        */
        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        __HAL_AFIO_REMAP_TIM1_PARTIAL();
    }
    
    {
        /* USER CODE BEGIN TIM1_Init 0 */

        /* USER CODE END TIM1_Init 0 */

        TIM_ClockConfigTypeDef sClockSourceConfig = {0};
        TIM_MasterConfigTypeDef sMasterConfig = {0};
        TIM_OC_InitTypeDef sConfigOC = {0};
        TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

        /* USER CODE BEGIN TIM1_Init 1 */

        /* USER CODE END TIM1_Init 1 */
        htim1.Instance = TIM1;
        htim1.Init.Prescaler = 71;
        htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim1.Init.Period = 999;
        htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim1.Init.RepetitionCounter = 0;
        htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
        if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
        {
            Error_Handler();
        }
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
        {
            Error_Handler();
        }
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
        {
            Error_Handler();
        }
        sConfigOC.OCMode = TIM_OCMODE_PWM2;
        sConfigOC.Pulse = 499;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
        sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
        sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
        if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
        {
            Error_Handler();
        }
        sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
        sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
        sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
        sBreakDeadTimeConfig.DeadTime = 0;
        sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
        sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
        sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
        if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
        {
            Error_Handler();
        }
        /* USER CODE BEGIN TIM1_Init 2 */

        /* USER CODE END TIM1_Init 2 */
        HAL_TIM_MspPostInit(&htim1);
    }
    
    __HAL_TIM_ENABLE(&htim1);
    
    return 0;
}
INIT_BOARD_EXPORT(tim1_init);

/* 定时器超时回调函数 */
static int pwm1_ccr1(int argc, char *argv[])
{
    int i;
    rt_bool_t result;
    
    sscanf(argv[1], "%d", &i);
    if ( i < 0 || i > 1000)
    {
        rt_kprintf("error value:%s, please input value range [0-100] \n", argv[0]);
        return 0;
    }
    
    TIM1->CCR1 = i;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm1_ccr1, PWM Duty cycle);


