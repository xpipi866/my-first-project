#ifndef __BSP_DS18B20_H
#define __BSP_DS18B20_H
#include "sys.h" 

// ==========================================
//   在此处修改你的 DS18B20 引脚位置
// ==========================================
// 假设你用的是 PB12
#define DS18_PORT_GRP    GPIOA              // 端口组: GPIOB
#define DS18_PIN_NUM     7                 // 引脚号: 12
#define DS18_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE() // 时钟

// --- 下面的代码会自动根据上面的设置计算，不需要改 ---

// 1. 输入输出模式切换 (寄存器操作, 为了速度)
// 原理: MODER 寄存器每 2 位控制一个引脚。清零是输入，写01是输出。
#define DS18B20_IO_IN()  {DS18_PORT_GRP->MODER &= ~(3<<(DS18_PIN_NUM*2)); DS18_PORT_GRP->MODER |= 0<<(DS18_PIN_NUM*2);} 
#define DS18B20_IO_OUT() {DS18_PORT_GRP->MODER &= ~(3<<(DS18_PIN_NUM*2)); DS18_PORT_GRP->MODER |= 1<<(DS18_PIN_NUM*2);} 

// 2. 数据读写操作 (位带操作 或 HAL库读取)
// 为了兼容性，这里使用 HAL 库读取/写入引脚电平 (F429 速度够快，没问题)
#define DS18B20_DQ_OUT(val) HAL_GPIO_WritePin(DS18_PORT_GRP, (1<<DS18_PIN_NUM), (val?GPIO_PIN_SET:GPIO_PIN_RESET))
#define DS18B20_DQ_IN       (HAL_GPIO_ReadPin(DS18_PORT_GRP, (1<<DS18_PIN_NUM)))

// --- 函数声明 ---
uint8_t DS18B20_Init(void);          
short DS18B20_Get_Temp(void);        

#endif