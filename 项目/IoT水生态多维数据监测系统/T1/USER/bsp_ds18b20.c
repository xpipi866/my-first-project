#include "bsp_ds18b20.h"
#include "delay.h"

// 复位DS18B20
void DS18B20_Rst(void)
{
    DS18B20_IO_OUT(); 	// 设置为输出
    DS18B20_DQ_OUT(0); 	// 拉低
    delay_us(750);    	// 拉低750us
    DS18B20_DQ_OUT(1); 	// 拉高
    delay_us(15);     	// 15us
}

// 等待回应
uint8_t DS18B20_Check(void)
{
    uint8_t retry = 0;
    DS18B20_IO_IN(); 	// 设置为输入
    while (DS18B20_DQ_IN && retry < 200)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 200) return 1;
    else retry = 0;
    
    while (!DS18B20_DQ_IN && retry < 240)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 240) return 1;
    return 0;
}

// 初始化
uint8_t DS18B20_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    DS18_CLK_ENABLE(); // 开启时钟
    
    GPIO_Initure.Pin = (1 << DS18_PIN_NUM); // 自动计算引脚位
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIO_Initure.Pull = GPIO_PULLUP;        // 重要：开启内部上拉！
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(DS18_PORT_GRP, &GPIO_Initure);
    
    DS18B20_Rst();
    return DS18B20_Check();
}

// 读一位
uint8_t DS18B20_Read_Bit(void)
{
    uint8_t data;
    DS18B20_IO_OUT();
    DS18B20_DQ_OUT(0);
    delay_us(2);
    DS18B20_DQ_OUT(1);
    DS18B20_IO_IN();
    delay_us(12);
    if (DS18B20_DQ_IN) data = 1;
    else data = 0;
    delay_us(50);
    return data;
}

// 写一个字节
void DS18B20_Write_Byte(uint8_t dat)
{
    uint8_t j, testb;
    DS18B20_IO_OUT();
    for (j = 1; j <= 8; j++)
    {
        testb = dat & 0x01;
        dat = dat >> 1;
        if (testb) // 写1
        {
            DS18B20_DQ_OUT(0);
            delay_us(2);
            DS18B20_DQ_OUT(1);
            delay_us(60);
        }
        else // 写0
        {
            DS18B20_DQ_OUT(0);
            delay_us(60);
            DS18B20_DQ_OUT(1);
            delay_us(2);
        }
    }
}

// 读一个字节
uint8_t DS18B20_Read_Byte(void)
{
    uint8_t i, j, dat;
    dat = 0;
    for (i = 1; i <= 8; i++)
    {
        j = DS18B20_Read_Bit();
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}

// 开始转换
void DS18B20_Start(void)
{
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xCC); // skip rom
    DS18B20_Write_Byte(0x44); // convert
}

// 得到温度值
short DS18B20_Get_Temp(void)
{
    uint8_t temp;
    uint8_t TL, TH;
    short tem;
    
    DS18B20_Start();  // 1. 发送“开始转换”命令
    
    // 等待转换完成
    // DS18B20 12位精度最长需要 750ms
    // 这里我们直接死等 800ms，确保数据准确
    delay_ms(800);    
    
    DS18B20_Rst();    // 2. 复位，准备读数据
    DS18B20_Check();
    DS18B20_Write_Byte(0xCC); // skip rom
    DS18B20_Write_Byte(0xBE); // read scratchpad (读暂存器)
    
    TL = DS18B20_Read_Byte(); // LSB
    TH = DS18B20_Read_Byte(); // MSB
    
    if (TH > 7) // 负温度处理
    {
        TH = ~TH;
        TL = ~TL;
        temp = 0; // 标志位
    }
    else temp = 1;
    
    tem = TH;
    tem <<= 8;
    tem += TL;
    
    // 转换为实际温度值 (扩大10倍)
    tem = (float)tem * 0.625; 
    
    if (temp) return tem; // 返回正数
    else return -tem;     // 返回负数
}