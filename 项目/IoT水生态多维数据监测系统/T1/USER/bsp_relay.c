#include "bsp_relay.h"

// 初始化所有继电器引脚
void BSP_Relay_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    // 1. 开启所有用到的端口时钟
    HEATER_CLK_ENABLE();      // GPIOB
    FILTER_CLK_ENABLE();      // GPIOA
    PUMP_CLK_ENABLE();        // GPIOC (增氧泵, 投食器, 补水阀都在 C 口)
    // 注意：FEEDER 和 WATER_VALVE 也在 GPIOC，所以上面开启一次就够了

    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP;         // 上拉 (默认高电平，防止上电误动作)
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;

    // --- 2. 初始化各个引脚 ---
    
    // 加热棒 (PB0)
    GPIO_Initure.Pin = HEATER_PIN;
    HAL_GPIO_Init(HEATER_PORT, &GPIO_Initure);

    // 过滤器 (PA1)
    GPIO_Initure.Pin = FILTER_PIN;
    HAL_GPIO_Init(FILTER_PORT, &GPIO_Initure);

    // 增氧泵 (PC4) | 投食器 (PC5) | 补水阀 (PC1)
    // 因为它们都在 GPIOC，可以一次性初始化
    GPIO_Initure.Pin = PUMP_PIN | FEEDER_PIN | WATER_VALVE_PIN;
    HAL_GPIO_Init(PUMP_PORT, &GPIO_Initure);

    // --- 3. 默认状态：全部关闭 ---
    // 假设 RELAY_OFF 是 1 (高电平关闭)
    BSP_Relay_Set(DEV_HEATER, RELAY_OFF);
    BSP_Relay_Set(DEV_FILTER, RELAY_OFF);
    BSP_Relay_Set(DEV_PUMP, RELAY_OFF);
    BSP_Relay_Set(DEV_FEEDER, RELAY_OFF);
    BSP_Relay_Set(DEV_WATER_VALVE, RELAY_OFF);
}

// 统一控制函数
void BSP_Relay_Set(Relay_Device_ID dev, uint8_t state)
{
    // state: 传入 RELAY_ON 或 RELAY_OFF
    // (GPIO_PinState)state 将自动转换为 GPIO_PIN_RESET(0) 或 GPIO_PIN_SET(1)
    
    switch(dev)
    {
        case DEV_HEATER:
            HAL_GPIO_WritePin(HEATER_PORT, HEATER_PIN, (GPIO_PinState)state);
            break;

        case DEV_FILTER:
            HAL_GPIO_WritePin(FILTER_PORT, FILTER_PIN, (GPIO_PinState)state);
            break;

        case DEV_PUMP:
            HAL_GPIO_WritePin(PUMP_PORT, PUMP_PIN, (GPIO_PinState)state);
            break;
            
        case DEV_FEEDER:
            HAL_GPIO_WritePin(FEEDER_PORT, FEEDER_PIN, (GPIO_PinState)state);
            break;
            
        case DEV_WATER_VALVE:
            HAL_GPIO_WritePin(WATER_VALVE_PORT, WATER_VALVE_PIN, (GPIO_PinState)state);
            break;

        default:
            break;
    }
}