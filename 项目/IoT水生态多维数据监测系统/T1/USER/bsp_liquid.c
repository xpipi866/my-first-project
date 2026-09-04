#include "bsp_liquid.h"

void BSP_Liquid_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    LIQUID_CLK_ENABLE(); // 开启时钟

    GPIO_Initure.Pin = LIQUID_PIN;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;    // 输入模式
    GPIO_Initure.Pull = GPIO_PULLUP;        // 上拉 (默认高电平)
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    
    HAL_GPIO_Init(LIQUID_PORT, &GPIO_Initure);
}

// 读取水位状态
// 返回: WATER_LEVEL_OK (水足) 或 WATER_LEVEL_LOW (缺水)
uint8_t BSP_Liquid_Read(void)
{
    // 如果引脚读取到低电平(0)，说明开关对地闭合
    if(HAL_GPIO_ReadPin(LIQUID_PORT, LIQUID_PIN) == GPIO_PIN_RESET)
    {
        return WATER_LEVEL_OK; // 水是满的
    }
    else
    {
        return WATER_LEVEL_LOW; // 悬空，缺水了
    }
}