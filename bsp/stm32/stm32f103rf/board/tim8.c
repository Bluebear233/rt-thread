#include "main.h"
#include "board.h"
/* USER CODE BEGIN Includes */
#include <drv_common.h>
/* USER CODE END Includes */
#include <stdio.h>

static TIM_HandleTypeDef htim8;

#define OC_CNT_MAX 1000 - 1 

static int tim8_init(void)
{
    // GPIO INIT
    {
				GPIO_InitTypeDef GPIO_InitStruct = {0};
				__HAL_RCC_GPIOC_CLK_ENABLE();
				/**TIM8 GPIO Configuration
				PC6     ------> TIM8_CH1
				PC7     ------> TIM8_CH2
				PC8     ------> TIM8_CH3
				PC9     ------> TIM8_CH4
				*/
				GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);    
					__HAL_AFIO_REMAP_TIM1_PARTIAL();
    }
    
    {
				/* USER CODE BEGIN TIM8_Init 0 */

				/* USER CODE END TIM8_Init 0 */

				TIM_ClockConfigTypeDef sClockSourceConfig = {0};
				TIM_MasterConfigTypeDef sMasterConfig = {0};
				TIM_OC_InitTypeDef sConfigOC = {0};
				TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

				/* USER CODE BEGIN TIM8_Init 1 */

				/* USER CODE END TIM8_Init 1 */
				htim8.Instance = TIM8;
				htim8.Init.Prescaler = 72-1;
				htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
				htim8.Init.Period = 1000;
				htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
				htim8.Init.RepetitionCounter = 0;
				htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
				if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
				{
					Error_Handler();
				}
				sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
				if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
				{
					Error_Handler();
				}
				if (HAL_TIM_OC_Init(&htim8) != HAL_OK)
				{
					Error_Handler();
				}
				sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
				sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
				if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
				{
					Error_Handler();
				}
				sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
				sConfigOC.Pulse = 200;
				sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
				sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
				sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
				sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
				sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
				if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
				{
					Error_Handler();
				}
				sConfigOC.Pulse = 400;
				if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
				{
					Error_Handler();
				}
				sConfigOC.Pulse = 600;
				if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
				{
					Error_Handler();
				}
				sConfigOC.Pulse = 800;
				if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
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
				if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
				{
					Error_Handler();
				}
				/* USER CODE BEGIN TIM8_Init 2 */

				/* USER CODE END TIM8_Init 2 */
				HAL_TIM_MspPostInit(&htim8);

				
    }
    
    // __HAL_TIM_ENABLE(&htim2);
		
    return 0;
}
INIT_BOARD_EXPORT(tim8_init);

static volatile unsigned int ic1v,ic2v;

/* 定时器超时回调函数 */
static int tim8(int argc, char *argv[])
{
		rt_kprintf("chanle1:%d\n", ic1v);
		rt_kprintf("chanle1:%d\n", ic2v);
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(tim8 ,test PWM Duty cycle);

