#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H

#include "sys.h" 
// 或者 #include "stm32f4xx_hal.h" 
// 绝对不能写 #include "bsp_relay.h" !!!

// ================= 硬件引脚配置区 =================

// 1. 加热棒 (PB0)
#define HEATER_PIN          GPIO_PIN_0
#define HEATER_PORT         GPIOB
#define HEATER_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

// 2. 过滤器 (PA1)
#define FILTER_PIN          GPIO_PIN_1
#define FILTER_PORT         GPIOA
#define FILTER_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

// 3. 增氧泵 (PC4)
#define PUMP_PIN            GPIO_PIN_4
#define PUMP_PORT           GPIOC
#define PUMP_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()

// 4. 投食器 (PC5)
#define FEEDER_PIN          GPIO_PIN_5
#define FEEDER_PORT         GPIOC   
#define FEEDER_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

// 5. 补水阀 (PC1)
#define WATER_VALVE_PIN          GPIO_PIN_1
#define WATER_VALVE_PORT         GPIOC
#define WATER_VALVE_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

// =================================================

// 设备 ID
typedef enum {
    DEV_HEATER = 0,
    DEV_FILTER,
    DEV_PUMP,
    DEV_FEEDER,
    DEV_WATER_VALVE
} Relay_Device_ID;

// 状态 (0吸合/1断开 还是 1吸合/0断开，取决于你的继电器模块)
// 通常继电器是低电平触发(Low Trigger)，即0是开
#define RELAY_ON   0
#define RELAY_OFF  1

// 函数声明
void BSP_Relay_Init(void);
void BSP_Relay_Set(Relay_Device_ID dev, uint8_t state);

#endif