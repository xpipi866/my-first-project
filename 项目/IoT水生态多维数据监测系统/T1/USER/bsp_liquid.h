#ifndef __BSP_LIQUID_H
#define __BSP_LIQUID_H

#include "stm32f4xx_hal.h"

// --- 修改为 PH2 (对应板子上的 KEY2 引脚) ---
#define LIQUID_PIN          GPIO_PIN_2
#define LIQUID_PORT         GPIOH
#define LIQUID_CLK_ENABLE() __HAL_RCC_GPIOH_CLK_ENABLE()

// --- 逻辑定义 ---
// 非接触传感器(NPN型): 无水悬空(1), 有水导通(0)
#define WATER_LEVEL_OK      0  // 读到 0 代表有水
#define WATER_LEVEL_LOW     1  // 读到 1 代表缺水

// --- 函数 ---
void BSP_Liquid_Init(void);
uint8_t BSP_Liquid_Read(void);

#endif