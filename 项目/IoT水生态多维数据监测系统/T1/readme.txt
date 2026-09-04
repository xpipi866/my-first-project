实验器材:
	阿波罗STM32F429开发板
	
实验目的:
	学习STM32内部ADC的使用
	
硬件资源:
	1,DS0(连接在PB1) 
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面) 
	3,ALIENTEK 2.8/3.5/4.3/7寸LCD模块(包括MCU屏和RGB屏,都支持) 
	4,ADC(STM32内部ADC1,通道5,即:ADC1_CH5)	
	
实验现象:
	本实验通过STM32内部ADC1读取通道5（PA5）上面的电压，在LCD模块上面显示ADC转换值以及换算成电压后
	的电压值。
	
注意事项:
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在lcd.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!
	3,PA5默认通过跳线帽连接TPAD,读取到的电压值约为3.3V左右,请拔了P11跳线帽,然后给PA5提供测试电压.
	4,ADC的最大输入电压是3.3V,请不要超过这个值.
	5,多功能接口(P11)的ADC即连接在PA5上.
	6,ADC的参考电压默认通过P5连接在3.3V上面,所以默认参考电压是3.3V
	 

	 
参考资料：阿波罗STM32F429开发指南-库函数版本.pdf 第二十四章


-------------------------------------------------------------------------------------------

◆其他重要连接：
  开发板光盘资料下载地址（视频+文档+源码等）：http://www.openedv.com/posts/list/13912.htm


◆友情提示：如果您想以后及时免费的收到正点原子所有开发板资料更新增加通知，请关注微信公众平台：
 2种添加方法：（动动手提升您的学习效率，惊喜不断哦）
（1）打开微信->添加朋友->公众号->输入“正点原子”->点击关注
（2）打开微信->添加朋友->输入“alientek_stm32"->点击关注
 具体微信添加方法，请参考帖子：http://www.openedv.com/posts/list/45157.htm
 


						

						淘宝店铺： http://openedv.taobao.com
						           http://eboard.taobao.com
						公司网站：www.alientek.com
						技术论坛：www.openedv.com
                                                微信公众平台：正点原子
						电话：020-38271790
						传真：020-36773971
						广州市星翼电子科技有限公司
						正点原子@ALIENTEK
						     2016-6月

//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "key.h"
//#include "lcd.h"
//#include "sdram.h"
//#include "adc.h"
//int main(void)
//{
//    u16 adcx;
//    float voltage, turbidity;
//    float TU = 0.0;
//    float TU_calibration = 0.0;
//    float TU_value = 0.0;
//    float temp_data = 250.0;  // 温度值，假设为 25.0 °C 需要根据实际温度获取
//    float K_Value = 3203.0;   // 校准系数，参考代码中的常量

//    HAL_Init();
//    Stm32_Clock_Init(360,25,2,8);
//    delay_init(180);
//    uart_init(115200);
//    LED_Init();
//    SDRAM_Init();
//    LCD_Init();
//    MY_ADC_Init();  // 使用修改后的初始化

//    // LCD界面初始化
//    LCD_Clear(WHITE);
//    POINT_COLOR = RED;
//    LCD_ShowString(30,50,200,16,16,"Apollo STM32F4/F7");
//    LCD_ShowString(30,70,200,16,16,"Turbidity Sensor");
//    LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");

//    POINT_COLOR = BLUE;
//    LCD_ShowString(30,130,200,16,16,"ADC Value:");
//    LCD_ShowString(30,150,200,16,16,"Voltage:0.000V");
//    LCD_ShowString(30,170,200,16,16,"Turbidity:0.0 NTU");

//    while(1)
//    {
//        adcx = Get_Adc_Average(ADC_CHANNEL_11, 10);  // 使用通道11
//        voltage = adcx * 3.3f / 4095.0f;
//        
//        // 浊度计算公式（根据手册公式）
//        TU = voltage / 0.66f;  // 基本浊度计算公式，ADC转化为电压后计算
//        TU_calibration = -0.0192f * (temp_data / 10.0f - 25.0f) + TU;  // 温度补偿
//        TU_value = -865.68f * TU_calibration + K_Value;  // 浊度值计算

//        // 限制浊度值范围
//        if (TU_value <= 0) TU_value = 0;
//        if (TU_value >= 3000) TU_value = 3000;

//        // 显示ADC原始值
//        LCD_ShowxNum(134,130,adcx,4,16,0);

//        // 显示电压值
//        LCD_ShowxNum(134,150,(u16)voltage,1,16,0);
//        voltage -= (u16)voltage;
//        LCD_ShowxNum(150,150,(u16)(voltage * 1000),3,16,0X80);
//        
//        // 显示浊度值
//        LCD_ShowxNum(134,170,(u16)TU_value,4,16,0);
//        TU_value -= (u16)TU_value;
//        LCD_ShowxNum(158,170,(u16)(TU_value * 10),1,16,0X80);

//        LED0 = !LED0;  // 控制LED
//        delay_ms(500);
//    }
//}
