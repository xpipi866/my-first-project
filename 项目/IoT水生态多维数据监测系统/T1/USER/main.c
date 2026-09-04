//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "sdram.h"
//#include "lcd.h"
//#include "touch.h"
//#include "24cxx.h"
//#include "adc.h"
//#include "fish_tank_data.h"
//#include "bsp_relay.h"
//#include "bsp_ds18b20.h"
//#include "bsp_liquid.h"
//#include "stdio.h"
//#include "string.h"
//#include "stdlib.h"
//#include "text.h" 
//#include "stm32f4xx_hal.h" 

//// ==========================================
////  【配置区】
//// ==========================================
//#define RATIO_LEFT       0.44f
//#define RATIO_RIGHT      0.56f
//#define LAYOUT_GAP       10
//#define LAYOUT_TOP_Y     40
//#define LAYOUT_MAIN_H    520
//#define DEFAULT_TARGET_TEMP  26.0f
//#define LOG_MAX_HISTORY      300
//#define FONT_SIZE_TITLE  24
//#define FONT_SIZE_TEXT   16

//#define COLOR_BG        0x1082 
//#define COLOR_CARD      0x2124 
//#define COLOR_ACCENT    0x051D 
//#define COLOR_TEXT_V    0xAEBE 
//#define COLOR_BTN_GRAY  0x7BEF 
//#define COLOR_BTN_RED   0xF800 
//#define COLOR_BTN_GRN   0x07E0 
//#define COLOR_BTN_BLU   0x051F 
//#define COLOR_BTN_FEED  0x07E0 
//#define COLOR_GOOD      0x07E0 
//#define COLOR_WARN      0xF800 
//#define COLOR_SET_TEXT   0x07FF 
//#define COLOR_SET_BORDER 0x07FF 
//#define C_WHITE         0xFFFF

//// --- [新增] 如果你的继电器只有4路，你需要为补水泵重新分配一个。这里暂时定义为4，请在bsp_relay.h中真实定义 ---
//#ifndef DEV_REFILL_PUMP
//#define DEV_REFILL_PUMP  4 
//#endif

//// 全局变量区加入
//#define WIFI_RX_BUF_SIZE  512
//char wifi_rx_buf[WIFI_RX_BUF_SIZE];
//int  wifi_rx_len = 0;

//// 全局变量
//float target_temp = DEFAULT_TARGET_TEMP;
//float saved_temp_mirror = DEFAULT_TARGET_TEMP; // 温度镜像

//// 其他参数的镜像
//u8 saved_filter_mode = 1, saved_filter_on_time = 20;
//u8 saved_pump_mode = 1, saved_pump_pulse_sec = 30;
//u8 saved_feeder_mode = 2, saved_feeder_period_hours = 12;
//u32 sys_tick_counter = 0; 

//RTC_HandleTypeDef hrtc;
//UART_HandleTypeDef UART3_Handler; // 这是专门给 WiFi 模块用的“对讲机”

//u8 filter_mode = 1; u8 filter_on_time = 20; 
//u8 pump_mode = 1; u8 pump_pulse_sec = 30; 
//u8 feeder_mode = 2; u8 feeder_period_hours = 12; 
//u32 last_feed_tick = 0; u8 feeding_state = 0; u8 feed_timer = 0;      
//u8 water_status = 0; u8 heater_state = 0; u8 filter_running = 0; u8 pump_running = 0; 
//u16 SCR_W = 800; u16 SCR_H = 480;

//// --- [新增] 新传感器的全局状态变量 ---
//u8 sensor_high_status = 0; // 鱼缸高水位状态
//u8 tank_water_status = 0;  // 补水箱状态：0有水，1缺水
//u8 food_level_status = 0;  // 鱼粮状态：0充足，1短缺
//u8 filling_water = 0;      // 补水泵运行状态：0停止，1补水中

//// 日志系统
//int show_log_count = 3;   
//char log_pool[LOG_MAX_HISTORY][120]; 
//int log_total_count = 0;   
//int log_view_offset = 0;   
//short last_touch_y = -1;   

//// 布局变量
//u16 LEFT_CARD_W, RIGHT_CARD_W;
//u16 LEFT_X, RIGHT_X;
//u16 LOG_Y, LOG_W;
//int LOG_H_DYNAMIC;
//u16 UI_TEMP_Y, UI_FILTER_Y, UI_PUMP_Y, UI_FEEDER_Y;
//u16 GAP_Y; 

//#define BTN_W         62    
//#define BTN_GAP       15    
//#define BAR_H         36    
//#define TOTAL_BAR_W   (BTN_W * 3 + BTN_GAP * 2) 

//#define WIFI_SSID     "KIKI"
//#define WIFI_PWD      "se4dr5ft6"
//#define ATK_DEV_ID    "08719037788807742917"
//#define ATK_DEV_PWD   "12345678"

//// ==========================================
////  【巴法云配置区】
//// ==========================================
//#define BEMFA_UID   "8b1f4af3386240b7993525552354d55b" 
//#define BEMFA_TOPIC "FishTank"  // 这里填你刚才新建的主题名字

//// ==========================================
////  功能函数
//// ==========================================
//void Wipe_Area(u16 x, u16 y, u16 w, u16 h) {
//    LCD_Fill(x, y, x + w, y + h, COLOR_CARD);
//}


//// 彻底统一的传感器初始化
//void Extra_Sensors_Init(void) {
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    
//    __HAL_RCC_GPIOH_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE(); // 开启 GPIOA 时钟

//    // 1. PH2(鱼粮), PH3(补水箱)
//    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_PULLUP; 
//    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
//    
//    // 2. [修改] 把 PA4(高位) 和 PA8(低位) 一起初始化！
//    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_8;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_PULLUP; 
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//}

//void App_Sync_Time(u8 year, u8 month, u8 date, u8 hour, u8 min, u8 sec) {
//    RTC_TimeTypeDef sTime = {0};
//    RTC_DateTypeDef sDate = {0};
//    sTime.Hours = hour; sTime.Minutes = min; sTime.Seconds = sec;
//    sDate.Year = year; sDate.Month = month; sDate.Date = date;
//    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//}

//void RTC_Init_NoBattery(void) {
//    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

//    __HAL_RCC_PWR_CLK_ENABLE();
//    HAL_PWR_EnableBkUpAccess();

//    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
//    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
//        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
//        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
//        HAL_RCC_OscConfig(&RCC_OscInitStruct);
//        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
//    } else {
//        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
//    }

//    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
//    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
//    __HAL_RCC_RTC_ENABLE();

//    hrtc.Instance = RTC;
//    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
//    hrtc.Init.AsynchPrediv = 127;
//    hrtc.Init.SynchPrediv = 255;
//    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
//    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
//    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
//    HAL_RTC_Init(&hrtc);

//    RTC_TimeTypeDef sTime = {0};
//    RTC_DateTypeDef sDate = {0};
//    char date_str[] = __DATE__; char time_str[] = __TIME__; 
//    sTime.Hours = atoi(time_str); sTime.Minutes = atoi(&time_str[3]); sTime.Seconds = atoi(&time_str[6]);
//    sDate.Year = atoi(&date_str[7]) - 2000;
//    if(date_str[4] == ' ') sDate.Date = atoi(&date_str[5]); else sDate.Date = atoi(&date_str[4]);
//    if(strncmp(date_str,"Jan",3)==0) sDate.Month=1; else if(strncmp(date_str,"Feb",3)==0) sDate.Month=2; 
//    else if(strncmp(date_str,"Mar",3)==0) sDate.Month=3; else if(strncmp(date_str,"Apr",3)==0) sDate.Month=4; 
//    else if(strncmp(date_str,"May",3)==0) sDate.Month=5; else if(strncmp(date_str,"Jun",3)==0) sDate.Month=6; 
//    else if(strncmp(date_str,"Jul",3)==0) sDate.Month=7; else if(strncmp(date_str,"Aug",3)==0) sDate.Month=8; 
//    else if(strncmp(date_str,"Sep",3)==0) sDate.Month=9; else if(strncmp(date_str,"Oct",3)==0) sDate.Month=10; 
//    else if(strncmp(date_str,"Nov",3)==0) sDate.Month=11; else if(strncmp(date_str,"Dec",3)==0) sDate.Month=12;

//    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//}

//void Update_Log_UI(void) {
//    int i;
//    u16 lx = LAYOUT_GAP + 20; 
//    u16 ly = LOG_Y + 45; 
//    u16 text_width = LOG_W - 40; 
//    show_log_count = (LOG_H_DYNAMIC - 50) / 20;
//    if(show_log_count < 1) show_log_count = 1;
//    Wipe_Area(lx, ly, text_width, show_log_count * 20);
//    for(i=0; i<show_log_count; i++) {
//        int pool_idx = log_view_offset + i;
//        if(pool_idx < log_total_count) {
//            BACK_COLOR = COLOR_CARD;
//            if(log_view_offset == 0 && i == 0) POINT_COLOR = C_WHITE;
//            else POINT_COLOR = COLOR_TEXT_V; 
//            Show_Str(lx, ly + i*20, text_width, FONT_SIZE_TEXT, (u8*)log_pool[pool_idx], 16, 0);
//        }
//    }
//    u16 bar_x = SCR_W - 15; u16 bar_h = show_log_count * 20;
//    LCD_Fill(bar_x, ly, bar_x+3, ly + bar_h, COLOR_BG);
//    if(log_total_count > show_log_count) {
//        u16 slider_h = bar_h / (log_total_count/show_log_count + 1);
//        if(slider_h < 10) slider_h = 10;
//        float p = (float)log_view_offset / (log_total_count - show_log_count);
//        u16 slider_y = ly + (u16)(p * (bar_h - slider_h));
//        LCD_Fill(bar_x, slider_y, bar_x+3, slider_y + slider_h, COLOR_ACCENT);
//    }
//}

//void Log_Add(char* text) {
//    int i; char buf[120];
//    RTC_TimeTypeDef sTime; RTC_DateTypeDef sDate;
//    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//    
//    sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d] %s", 
//            sDate.Year, sDate.Month, sDate.Date, 
//            sTime.Hours, sTime.Minutes, sTime.Seconds, 
//            text);
//            
//    for(i = LOG_MAX_HISTORY-1; i > 0; i--) strcpy(log_pool[i], log_pool[i-1]);
//    strcpy(log_pool[0], buf);
//    if(log_total_count < LOG_MAX_HISTORY) log_total_count++;
//    log_view_offset = 0; 
//    Update_Log_UI();
//}

//void Load_Settings(void) {
//    u16 temp_int = (AT24CXX_ReadOneByte(0) << 8) | AT24CXX_ReadOneByte(1);
//    if(temp_int > 400 || temp_int < 100) target_temp = DEFAULT_TARGET_TEMP; 
//    else target_temp = (float)temp_int / 10.0f;
//    
//    filter_mode = AT24CXX_ReadOneByte(2); if(filter_mode>2) filter_mode=1;
//    filter_on_time = AT24CXX_ReadOneByte(3); if(filter_on_time>60) filter_on_time=20;
//    pump_mode = AT24CXX_ReadOneByte(4); if(pump_mode>2) pump_mode=1;
//    pump_pulse_sec = AT24CXX_ReadOneByte(5); if(pump_pulse_sec>120) pump_pulse_sec=30;
//    feeder_mode = AT24CXX_ReadOneByte(6); if(feeder_mode>2) feeder_mode=2;
//    feeder_period_hours = AT24CXX_ReadOneByte(7); if(feeder_period_hours!=12 && feeder_period_hours!=24) feeder_period_hours=12;
//    
//    // 启动时同步所有镜像
//    saved_temp_mirror = target_temp;
//    saved_filter_mode = filter_mode; saved_filter_on_time = filter_on_time;
//    saved_pump_mode = pump_mode; saved_pump_pulse_sec = pump_pulse_sec;
//    saved_feeder_mode = feeder_mode; saved_feeder_period_hours = feeder_period_hours;
//}

//void Save_Settings(void) {
//    // 只有发生改变时才写入，必须加入 5ms 物理写入等待时间，否则必丢数据！
//    if(target_temp != saved_temp_mirror) {
//        u16 temp_int = (u16)(target_temp * 10);
//        AT24CXX_WriteOneByte(0, temp_int >> 8); delay_ms(5); 
//        AT24CXX_WriteOneByte(1, temp_int & 0xFF); delay_ms(5);
//        saved_temp_mirror = target_temp;
//    }
//    
//    if(filter_mode != saved_filter_mode) { AT24CXX_WriteOneByte(2, filter_mode); delay_ms(5); saved_filter_mode = filter_mode; }
//    if(filter_on_time != saved_filter_on_time) { AT24CXX_WriteOneByte(3, filter_on_time); delay_ms(5); saved_filter_on_time = filter_on_time; }
//    
//    if(pump_mode != saved_pump_mode) { AT24CXX_WriteOneByte(4, pump_mode); delay_ms(5); saved_pump_mode = pump_mode; }
//    if(pump_pulse_sec != saved_pump_pulse_sec) { AT24CXX_WriteOneByte(5, pump_pulse_sec); delay_ms(5); saved_pump_pulse_sec = pump_pulse_sec; }
//    
//    if(feeder_mode != saved_feeder_mode) { AT24CXX_WriteOneByte(6, feeder_mode); delay_ms(5); saved_feeder_mode = feeder_mode; }
//    if(feeder_period_hours != saved_feeder_period_hours) { AT24CXX_WriteOneByte(7, feeder_period_hours); delay_ms(5); saved_feeder_period_hours = feeder_period_hours; }
//}

//void Draw_CN_Btn(u16 x, u16 y, u16 w, u16 h, u16 color, char* text) {
//    LCD_Fill(x, y, x + w, y + h, color);
//    BACK_COLOR = color; POINT_COLOR = C_WHITE;
//    u16 tx = x + (w - strlen(text)*8) / 2; u16 ty = y + (h - 16) / 2;
//    Show_Str(tx, ty, w, 16, (u8*)text, 16, 0);
//}

//void Draw_Circle_Btn(u16 x, u16 y, u16 r, u16 color, char* symbol) {
//    int i, j;
//    for(i = x-r; i <= x+r; i++) {
//        for(j = y-r; j <= y+r; j++) { if( (i-x)*(i-x) + (j-y)*(j-y) <= r*r ) LCD_Fast_DrawPoint(i, j, color); }
//    }
//    BACK_COLOR = color; POINT_COLOR = C_WHITE;
//    LCD_ShowString(x-4, y-8, 50, 16, 16, (u8*)symbol); 
//}

//void Draw_CN_Setting_Frame(u16 btn_y, u8 mode, char* text) {
//    u16 right_w = RIGHT_CARD_W - 20;
//    u16 center_x = RIGHT_X + RIGHT_CARD_W / 2;
//    u16 start_x = center_x - TOTAL_BAR_W / 2;
//    u16 text_y = btn_y + BAR_H + 5; 
//    Wipe_Area(RIGHT_X + 5, text_y - 5, right_w + 10, 32); 
//    if(mode == 2) {
//        POINT_COLOR = COLOR_SET_BORDER; LCD_DrawRectangle(start_x, text_y, start_x + TOTAL_BAR_W, text_y + 24);
//        BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_SET_TEXT; 
//        u16 tx = start_x + (TOTAL_BAR_W - strlen(text)*8) / 2;
//        Show_Str(tx, text_y + 4, TOTAL_BAR_W, 16, (u8*)text, 16, 0);
//    }
//}

//void Update_Filter_UI(void) {
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
//    Show_Str(start_x, UI_FILTER_Y - 25, 200, 16, (u8*)"循环过滤系统", 16, 0);
//    Draw_CN_Btn(start_x, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
//    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==1?COLOR_BTN_GRN:COLOR_BTN_GRAY), "开");
//    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
//    char buf[30]; sprintf(buf, "开启: %d 分钟/小时", filter_on_time); Draw_CN_Setting_Frame(UI_FILTER_Y, filter_mode, buf); 
//}

//void Update_Pump_UI(void) {
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
//    Show_Str(start_x, UI_PUMP_Y - 25, 200, 16, (u8*)"增氧泵控制", 16, 0);
//    Draw_CN_Btn(start_x, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
//    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==1?COLOR_BTN_GRN:COLOR_BTN_GRAY), "开");
//    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
//    char buf[30]; sprintf(buf, "周期: %d 秒/次", pump_pulse_sec); Draw_CN_Setting_Frame(UI_PUMP_Y, pump_mode, buf);
//}

//void Update_Feeder_UI(void) {
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
//    Show_Str(start_x, UI_FEEDER_Y - 25, 200, 16, (u8*)"自动喂食机", 16, 0);
//    Draw_CN_Btn(start_x, UI_FEEDER_Y, BTN_W, BAR_H, (feeder_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
//    u16 feed_btn_color = feeding_state ? COLOR_BTN_FEED : COLOR_BTN_GRAY;
//    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_FEEDER_Y, BTN_W, BAR_H, feed_btn_color, (feeding_state?"...":"喂食"));
//    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_FEEDER_Y, BTN_W, BAR_H, (feeder_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
//    char buf[30]; sprintf(buf, "间隔: %d 小时", feeder_period_hours); Draw_CN_Setting_Frame(UI_FEEDER_Y, feeder_mode, buf);
//}

//// --- [修改] UI 监控视图，加入了补水箱和鱼粮的显示 ---
//void Update_Monitor_View(float cur_temp, float voltage, int purity) {
//    u16 lx = LEFT_X + 20; 
//    u16 ly = LAYOUT_TOP_Y + 45; 
//    u16 max_w = LEFT_CARD_W - 30; 
//    char buf[50];
//    Wipe_Area(lx, ly, max_w, 35); sprintf(buf, "%.1f", cur_temp);
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = C_WHITE; LCD_ShowString(lx, ly, 100, 32, 32, (u8*)buf);
//    Show_Str(lx + 80, ly + 12, 50, 16, (u8*)"℃", 16, 0);
//    
//    // 加大擦除区域，防止文字重叠
//    u16 y_cur = ly + 55; Wipe_Area(lx, y_cur, max_w, 300); 
//    
//    POINT_COLOR = (purity > 75 ? COLOR_GOOD : COLOR_WARN);
//    sprintf(buf, "水质: %d%% (%.2fV)", purity, voltage); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
//    
//    // [修改这一行代码，把高低水位的 0和1 真实值打印出来]
//    POINT_COLOR = (water_status==0?COLOR_GOOD:COLOR_WARN);
//    sprintf(buf, "水位: %s (H:%d L:%d)", (water_status==0?"正常":"警告"), sensor_high_status, water_status); 
//    Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
//    
//    // 新增：水箱和鱼粮状态
//    POINT_COLOR = (tank_water_status==0 ? COLOR_GOOD : COLOR_WARN);
//    sprintf(buf, "水箱: %s", (tank_water_status==0?"水量充足":"严重缺水")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

//    POINT_COLOR = (food_level_status==0 ? COLOR_GOOD : COLOR_WARN);
//    sprintf(buf, "鱼粮: %s", (food_level_status==0?"余量充足":"余量不足")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

//    POINT_COLOR = COLOR_BTN_GRAY;
//    sprintf(buf, "加热: %s", (heater_state?"开启":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
//    sprintf(buf, "过滤: %s", (filter_running?"运行":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
//    sprintf(buf, "增氧: %s", (pump_running?"运行":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
//    
//    POINT_COLOR = filling_water ? COLOR_BTN_BLU : COLOR_BTN_GRAY;
//    sprintf(buf, "补水: %s", (filling_water?"正在加水":"待机")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

//    POINT_COLOR = feeding_state ? COLOR_BTN_FEED : COLOR_BTN_GRAY;
//    sprintf(buf, "投食: %s", (feeding_state?"投放中":"待机")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0);
//}

//void Update_Target_View(void) {
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; 
//    char buf[20];
//    Wipe_Area(center_x - 70, UI_TEMP_Y - 60, 140, 25); 
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V; 
//    Show_Str(center_x - 48, UI_TEMP_Y - 55, 150, 16, (u8*)"目标温度设定", 16, 0);
//    sprintf(buf, "%.1f", target_temp); 
//    Wipe_Area(center_x - 30, UI_TEMP_Y - 10, 60, 30); 
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_ACCENT;
//    Show_Str(center_x - 24, UI_TEMP_Y - 8, 100, 24, (u8*)buf, 24, 0); 
//}

//void Draw_Card(u16 x, u16 y, u16 w, u16 h, u8 *title) {
//    LCD_Fill(x, y, x+w, y+h, COLOR_CARD); LCD_Fill(x, y, x+5, y+h, COLOR_ACCENT);
//    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V; Show_Str(x+15, y+10, 200, FONT_SIZE_TITLE, title, 24, 0);
//}

//void Draw_Dashboard(void) {
//    LCD_Clear(COLOR_BG); LCD_Fill(0, 0, SCR_W, 45, COLOR_ACCENT);
//    BACK_COLOR = COLOR_ACCENT; POINT_COLOR = C_WHITE; Show_Str(20, 10, 450, 24, (u8*)"智能鱼缸监控终端 V38.0", 24, 0);
//    
//    Draw_Card(LEFT_X, LAYOUT_TOP_Y, LEFT_CARD_W, LAYOUT_MAIN_H, (u8*)"实时监控");
//    Draw_Card(RIGHT_X, LAYOUT_TOP_Y, RIGHT_CARD_W, LAYOUT_MAIN_H, (u8*)"设备控制");
//    if(LOG_H_DYNAMIC > 20) Draw_Card(LAYOUT_GAP, LOG_Y, LOG_W, LOG_H_DYNAMIC, (u8*)"系统运行日志"); 
//    
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2;
//    Draw_Circle_Btn(center_x - 65, UI_TEMP_Y, 22, COLOR_BTN_GRAY, "-");
//    Draw_Circle_Btn(center_x + 65, UI_TEMP_Y, 22, COLOR_BTN_GRAY, "+");
//    
//    Update_Target_View();
//}

//// [新增] 初始化连接 WiFi 模块的串口3 (PB10=TX, PB11=RX)
//void WiFi_Serial_Init(u32 baudrate) {
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_USART3_CLK_ENABLE();
//    
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//    
//    UART3_Handler.Instance = USART3;
//    UART3_Handler.Init.BaudRate = baudrate;
//    UART3_Handler.Init.WordLength = UART_WORDLENGTH_8B;
//    UART3_Handler.Init.StopBits = UART_STOPBITS_1;
//    UART3_Handler.Init.Parity = UART_PARITY_NONE;
//    UART3_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//    UART3_Handler.Init.Mode = UART_MODE_TX_RX;
//    HAL_UART_Init(&UART3_Handler);
//	
//	
//}



//// [新增] 破冰测试：喊一句 AT，听听有没有 OK
//void WiFi_Test_Communication(void) {
//    char cmd[] = "AT\r\n";
//    u8 rx_byte;
//    u8 success = 0;
//    int i;
//    
//    Log_Add("系统: 正在呼叫 WiFi 模块...");
//    // 1. 发送暗号 "AT"
//    HAL_UART_Transmit(&UART3_Handler, (u8*)cmd, strlen(cmd), 1000);
//    
//    // 2. 竖起耳朵听有没有回复 'O' 和 'K'
//    for(i = 0; i < 100; i++) { 
//        // 每次等 10 毫秒，最多等 100 次 (大约1秒)
//        if(HAL_UART_Receive(&UART3_Handler, &rx_byte, 1, 10) == HAL_OK) {
//            if(rx_byte == 'O') {
//                success = 1; // 听到了大写的 O，基本就是 OK 了！
//                break;
//            }
//        }
//    }
//    
//    // 3. 把结果打在屏幕上
//    if(success) {
//        Log_Add("成功: WiFi 模块已回答 OK！");
//    } else {
//        Log_Add("失败: WiFi 模块装死无响应...");
//    }
//}

//// 发送AT指令并等待响应
//// 返回值: 1 成功; 0 失败
//u8 WiFi_Send_Cmd(char *cmd, char *ack, u32 timeout)
//{
//    u8 len = 0;
//    char rx_buf[256] = {0};
//    
//    // 1. 清空串口3接收缓冲区 (假设你已经有了串口接收中断或缓存)
//    // 这里简单处理：发送前先清空单片机的接收缓存
//    memset(rx_buf, 0, 256); 
//    
//    // 2. 发送指令
//    HAL_UART_Transmit(&UART3_Handler, (u8*)cmd, strlen(cmd), 100);
//    
//    // 3. 循环等待响应
//    u32 t = 0;
//    while(t < timeout)
//    {
//        // 建议在串口3中断里把数据存入一个全局缓冲区，这里检查该缓冲区
//        // 临时方案：直接轮询接收（不推荐，但如果你没写中断逻辑可以用这个）
//        u8 res;
//        if(HAL_UART_Receive(&UART3_Handler, &res, 1, 10) == HAL_OK)
//        {
//            if(len < 250) rx_buf[len++] = res;
//            if(strstr(rx_buf, ack)) return 1; // 查到了预期的回复
//        }
//        t += 10;
//        
//    }
//    return 0; // 超时没收到回复
//}

//// 工业级 AT 雷达 (光速无睡版，专治漏字！)
//u8 Send_AT(char* cmd, char* ack, u32 timeout_ms) {
//    char buf[250] = {0};
//    int len = 0;
//    uint32_t tmp;
//    uint32_t start_time = HAL_GetTick(); // 记录开始时间，用作超时判断
//    
//    // 1. 发送前暴力清空所有残留和报错
//    tmp = USART3->SR; tmp = USART3->DR; (void)tmp;
//    
//    // 2. 发送指令
//    if(cmd != NULL) {
//        for(int i = 0; i < strlen(cmd); i++) {
//            USART3->DR = cmd[i]; 
//            // 等待发送时，也顺手吸干进来的回音
//            while((USART3->SR & (1<<7)) == 0) { 
//                if(USART3->SR & (1<<5)) { 
//                    char rx = USART3->DR; 
//                    if(rx >= 0x20 && rx <= 0x7E && len < 100) buf[len++] = rx;
//                }
//            }
//        }
//    }
//    
//    // 3. 极速扫描期（?? 里面绝对没有 delay 睡觉代码！）
//    while((HAL_GetTick() - start_time) < timeout_ms) {
//        // 只要听到声音，瞬间吸干！
//        if(USART3->SR & (1<<5)) { 
//            char rx = USART3->DR;
//            if(rx >= 0x20 && rx <= 0x7E && len < 240) buf[len++] = rx;
//            
//            // 只要凑齐了暗号(比如 OK)，直接凯旋！
//            if(strstr(buf, ack) != NULL) return 1; 
//        }
//        
//        // 终极保命：如果万一发生溢出(ORE标志)，立刻清空恢复！
//        if(USART3->SR & (1<<3)) { 
//            tmp = USART3->SR; tmp = USART3->DR; (void)tmp; 
//        }
//    }
//    
//    // 4. 打印遗言
//    if(len > 0) { 
//        buf[len] = '\0'; 
//        char log[120];
//        sprintf(log, "回话: %s", buf);
//        Log_Add(log); 
//    } else {
//        Log_Add("回话: [死寂无声]");
//    }
//    return 0; 
//}

//// [巴法云专属] 现代化 TCP 连云程序 (严格状态机时序版)
//void WiFi_Connect_Bemfa(void) {
//    Log_Add("系统: 准备连接巴法云 TCP 创客云...");
//    delay_ms(2500); 
//    
//    Log_Add("系统: 1. 测试指令通道...");
//    if(!Send_AT("AT\r\n", "OK", 1000)) { Log_Add("严重: 模块通讯失败！"); return; }
//    
//    Log_Add("系统: 1.5 初始化网络规矩...");
//    Send_AT("ATE0\r\n", "OK", 1000); 
//    Send_AT("AT+CWMODE=1\r\n", "OK", 1000);
//    Send_AT("AT+CIPMUX=0\r\n", "OK", 1000);  // 单连接模式 (透传的先决条件)
//    // ?? 注意：这里删除了提前开启透传的错误指令！
//    
//    Log_Add("系统: 2. 连接 KIKI 热点(20秒)...");
//    if(Send_AT("AT+CWJAP=\"KIKI\",\"se4dr5ft6\"\r\n", "OK", 20000)) {
//        Log_Add("-> 热点接入！强制等待分配IP...");
//        delay_ms(3000); 
//    } else {
//        Log_Add("-> 热点连接失败！"); return;
//    }
//    

//    Log_Add("系统: 3. 正在敲击巴法云大门...");
//    // 顺理成章地发起 TCP 连接
//    if(Send_AT("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r\n", "CONNECT", 10000)) {
//        Log_Add("-> TCP 握手成功！");
//    } else {
//        Log_Add("-> 服务器连接失败！"); return;
//    }

//    Log_Add("系统: 4. 开启透传通道...");
//    // ?? 核心修正：必须在 CONNECT 成功之后，才能开启透传！
//    Send_AT("AT+CIPMODE=1\r\n", "OK", 1000); 
//    Send_AT("AT+CIPSEND\r\n", ">", 1000); // 看到 > 符号代表通道已敞开

//    Log_Add("系统: 5. 发送设备上线报文...");
//    char sub_cmd[100];
//    sprintf(sub_cmd, "cmd=1&uid=%s&topic=%s\r\n", BEMFA_UID, BEMFA_TOPIC);
//    HAL_UART_Transmit(&UART3_Handler, (u8*)sub_cmd, strlen(sub_cmd), 500);
//    
//    delay_ms(1000);
//    Log_Add("==== 大满贯！巴法云通道已打开 ====");
//}


//void WiFi_Receive_And_Parse(void) {
//    u8 ch;
//    // 非阻塞接收：有数据就读，没数据立刻返回
//    while (HAL_UART_Receive(&UART3_Handler, &ch, 1, 0) == HAL_OK) {
//        if (ch == '\n') {
//            wifi_rx_buf[wifi_rx_len] = '\0';
//            // 开始解析这一行
//            char* buf = wifi_rx_buf;
//            
//            // --- 温度设定 ---
//            char* p = strstr(buf, "#settemp#:#");
//            if (p) {
//                float t = atof(p + 11);
//                if (t >= 15.0f && t <= 35.0f) {
//                    target_temp = t;
//                    Log_Add("云控: 目标温度已更新");
//                    Update_Target_View();
//                }
//            }
//            // --- 过滤器控制 ---
//            if (strstr(buf, "#filter#:#stop#"))       { filter_mode = 0; Update_Filter_UI(); Log_Add("云控: 过滤停止"); }
//            else if (strstr(buf, "#filter#:#on#"))    { filter_mode = 1; Update_Filter_UI(); Log_Add("云控: 过滤开启"); }
//            // --- 增氧控制 ---
//            if (strstr(buf, "#oxy#:#stop#"))          { pump_mode = 0; Update_Pump_UI(); Log_Add("云控: 增氧停止"); }
//            else if (strstr(buf, "#oxy#:#on#"))       { pump_mode = 1; Update_Pump_UI(); Log_Add("云控: 增氧开启"); }
//            // --- 过滤时间 ---
//            p = strstr(buf, "#filtertime#:#");
//            if (p) { filter_on_time = atoi(p + 14); Update_Filter_UI(); }
//            // --- 增氧时间 ---
//            p = strstr(buf, "#oxytime#:#");
//            if (p) { pump_pulse_sec = atoi(p + 11); Update_Pump_UI(); }
//            // --- 喂食 ---
//            if (strstr(buf, "#feed#:#once#")) {
//                if (!feeding_state) {
//                    BSP_Relay_Set(DEV_FEEDER, RELAY_ON);
//                    feeding_state = 1; feed_timer = 3;
//                    Log_Add("云控: 手动投食");
//                    Update_Feeder_UI();
//                }
//            }
//            if (strstr(buf, "#feed#:#autooff#") || strstr(buf, "#feed#:#stopall#")) {
//                feeder_mode = 0;
//                BSP_Relay_Set(DEV_FEEDER, RELAY_OFF);
//                feeding_state = 0;
//                Log_Add("云控: 投食禁用");
//                Update_Feeder_UI();
//            }
//            // --- 自动喂食时间 ---
//            p = strstr(buf, "#feedtime#:#");
//            if (p) {
//                int h = atoi(p + 12);
//                if (h == 12 || h == 24) { feeder_period_hours = h; Update_Feeder_UI(); }
//            }
//            
//            wifi_rx_len = 0; // 清空缓冲区
//        } else if (wifi_rx_len < WIFI_RX_BUF_SIZE - 1) {
//            wifi_rx_buf[wifi_rx_len++] = ch;
//        } else {
//            wifi_rx_len = 0; // 溢出保护
//        }
//    }
//}

//// ==========================================
////  6. Main 函数
//// ==========================================
//int main(void) {
//    short raw_temp; float temp_c; u16 adcx; float voltage; int purity;
//    int one_sec_counter = 0, idle_counter = 0; 
//    HAL_Init(); Stm32_Clock_Init(360, 25, 2, 8); delay_init(180); uart_init(115200);
//    BSP_Relay_Init(); BSP_Liquid_Init(); AT24CXX_Init(); SDRAM_Init(); LCD_Init(); tp_dev.init(); MY_ADC_Init(); 
//    
//    Extra_Sensors_Init(); // --- [新增] 初始化报警与补水传感器 ---

//    RTC_Init_NoBattery(); 
//    font_init(); 
//    
//    SCR_W = lcddev.width; SCR_H = lcddev.height; 
//    if(SCR_W == 0) { SCR_W = 800; SCR_H = 480; } 
//    
//    LEFT_CARD_W = (SCR_W - 3 * LAYOUT_GAP) * RATIO_LEFT;
//    RIGHT_CARD_W = (SCR_W - 3 * LAYOUT_GAP) * RATIO_RIGHT;
//    LEFT_X = LAYOUT_GAP;
//    RIGHT_X = LEFT_X + LEFT_CARD_W + LAYOUT_GAP;
//    LOG_Y = LAYOUT_TOP_Y + LAYOUT_MAIN_H + LAYOUT_GAP;
//    LOG_H_DYNAMIC = SCR_H - LOG_Y - 5; if(LOG_H_DYNAMIC < 50) LOG_H_DYNAMIC = 50; 
//    LOG_W = SCR_W - LAYOUT_GAP * 2;
//    
//    UI_TEMP_Y = LAYOUT_TOP_Y + 110;   // 下移20
//    UI_FILTER_Y = LAYOUT_TOP_Y + 175; // 下移20
//    GAP_Y = 105;                      // 间距收缩
//    UI_PUMP_Y = UI_FILTER_Y + GAP_Y;
//    UI_FEEDER_Y = UI_PUMP_Y + GAP_Y;
//    
//    Load_Settings(); Draw_Dashboard(); 
//    Update_Filter_UI(); Update_Pump_UI(); Update_Feeder_UI(); 
//    Log_Add("系统启动就绪..."); Log_Add("报警系统已挂载..."); 
//	
//	// --- 修改这里 ---
//    WiFi_Serial_Init(115200); 
//    WiFi_Connect_Bemfa(); // 调用上面写的逻辑
//    // ----------------
//    // ---------------------------------------------------

//    while(DS18B20_Init()) delay_ms(500); // 这行及以后的代码暂时不会跑了
//    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;

//    while(1) {
//		// ===== 临时调试：把WiFi收到的所有内容打到日志 =====
//    static char dbg_buf[256];
//    static int  dbg_len = 0;
//    u8 dbg_ch;
//    while(HAL_UART_Receive(&UART3_Handler, &dbg_ch, 1, 0) == HAL_OK) {
//        if(dbg_ch == '\n') {
//            dbg_buf[dbg_len] = '\0';
//            if(dbg_len > 0) {
//                Log_Add(dbg_buf);   // 直接显示在屏幕日志里
//                dbg_len = 0;
//            }
//        } else if(dbg_ch != '\r' && dbg_len < 250) {
//            dbg_buf[dbg_len++] = dbg_ch;
//        }
//    }
//    // ===== 调试结束 =====
//        tp_dev.scan(0);
//        if(tp_dev.sta & TP_PRES_DOWN) {
//            u16 x = tp_dev.x[0]; u16 y = tp_dev.y[0]; idle_counter = 0;
//            
//            if(y > (UI_TEMP_Y-40) && y < (UI_TEMP_Y+40)) {
//                if(x > center_x-90 && x < center_x-40) { target_temp -= 0.5f; Update_Target_View(); delay_ms(100); }
//                else if(x > center_x+40 && x < center_x+90) { target_temp += 0.5f; Update_Target_View(); delay_ms(100); }
//            }
//            else if(y > LOG_Y && y < LOG_Y + LOG_H_DYNAMIC) {
//                if(last_touch_y != -1) {
//                    short delta = y - last_touch_y;
//                    if(delta < -10) { if(log_view_offset < log_total_count - show_log_count) { log_view_offset++; Update_Log_UI(); } last_touch_y = y; }
//                    else if(delta > 10) { if(log_view_offset > 0) { log_view_offset--; Update_Log_UI(); } last_touch_y = y; }
//                } else { last_touch_y = y; }
//            }
//            else if(y > UI_FILTER_Y && y < UI_FILTER_Y + BAR_H) {
//                if(x > start_x && x < start_x + BTN_W) { if(filter_mode!=0){filter_mode=0; Log_Add("过滤: 停止");} }
//                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) { if(filter_mode!=1){filter_mode=1; Log_Add("过滤: 开启");} }
//                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(filter_mode!=2){filter_mode=2; Log_Add("过滤: 自动模式");} }
//                Update_Filter_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
//            }
//            else if(filter_mode == 2 && y > UI_FILTER_Y+BAR_H && y < UI_FILTER_Y+BAR_H+36) {
//                filter_on_time += 5; if(filter_on_time > 60) filter_on_time = 5; Update_Filter_UI(); delay_ms(150);
//            }
//            else if(y > UI_PUMP_Y && y < UI_PUMP_Y+BAR_H) {
//                if(x > start_x && x < start_x + BTN_W) { if(pump_mode!=0){pump_mode=0; Log_Add("增氧: 停止");} }
//                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) { if(pump_mode!=1){pump_mode=1; Log_Add("增氧: 开启");} }
//                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(pump_mode!=2){pump_mode=2; Log_Add("增氧: 自动模式");} }
//                Update_Pump_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
//            }
//            else if(pump_mode == 2 && y > UI_PUMP_Y+BAR_H && y < UI_PUMP_Y+BAR_H+36) {
//                pump_pulse_sec = (pump_pulse_sec==30?60:30); Update_Pump_UI(); delay_ms(150);
//            }
//            else if(y > UI_FEEDER_Y && y < UI_FEEDER_Y+BAR_H) {
//                if(x > start_x && x < start_x+BTN_W) { if(feeder_mode!=0){feeder_mode=0; Log_Add("投食: 禁用");} }
//                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) {
//                    if(!feeding_state) { Log_Add("手动投食启动"); BSP_Relay_Set(DEV_FEEDER, RELAY_ON); feeding_state = 1; feed_timer = 3; Update_Feeder_UI(); }
//                }
//                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(feeder_mode!=2){feeder_mode=2; Log_Add("投食: 自动模式");} }
//                Update_Feeder_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
//            }
//            else if(feeder_mode == 2 && y > UI_FEEDER_Y+BAR_H && y < UI_FEEDER_Y+BAR_H+36) {
//                feeder_period_hours = (feeder_period_hours==12? 24 : 12); Update_Feeder_UI(); delay_ms(150);
//            }
//        } else {
//            last_touch_y = -1; 
//            delay_ms(10);
//            if(++one_sec_counter >= 100) {
//                sys_tick_counter++; one_sec_counter = 0;
//                if(feeding_state && --feed_timer == 0) { BSP_Relay_Set(DEV_FEEDER, RELAY_OFF); feeding_state = 0; Log_Add("投食执行完毕"); Update_Feeder_UI(); }
//                if(feeder_mode == 2 && feeding_state == 0) {
//                    u32 interval = (feeder_period_hours == 12) ? 43200 : 86400; 
//                    if(sys_tick_counter - last_feed_tick >= interval) {
//                        BSP_Relay_Set(DEV_FEEDER, RELAY_ON); feeding_state = 1; feed_timer = 3; last_feed_tick = sys_tick_counter; Log_Add("自动投食开启"); Update_Feeder_UI(); 
//                    }
//                }
//            }
//            // ==========================================
//            //  核心传感器轮询与逻辑处理 (约 500ms 一次)
//            // ==========================================
//            if(++idle_counter > 50) {
//                Save_Settings(); 
//                
//                // --- 彻底抛弃 BSP_Liquid_Read，统一使用底层读取 ---
//                static u8 last_water = 0;
//                
//                // 1. 连续读取 4 个传感器的真实物理状态
//                water_status       = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8); // 鱼缸低位 (PA8)
//                sensor_high_status = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4); // 鱼缸高位
//                tank_water_status  = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_3); // 补水箱 (PH3)
//                food_level_status  = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_2); // 鱼粮 (PH2)
//                
//                // 3. 温度读取 (带滤波防错)
//                short temp_new = DS18B20_Get_Temp(); 
//                if(temp_new != 0 && temp_new != 850) {
//                    raw_temp = temp_new;
//                    temp_c = raw_temp / 10.0f;
//                }
//                
//                // 4. 水质读取
//                adcx = Get_Adc_Average(ADC_CHANNEL_5, 10); 
//                voltage = (float)adcx * (3.3f / 4096.0f);
//                purity = (voltage > 3.2f) ? 100 : (int)((voltage / 3.2f) * 100);
//                
//                // --- 5. 报警判定 ---
//                static u8 last_tank = 0, last_food = 0;
//                
//                if(water_status == 1 && last_water == 0) Log_Add("警报: 鱼缸水位过低!");
//                else if(water_status == 0 && last_water == 1) Log_Add("提示: 鱼缸水位已恢复.");
//                last_water = water_status;

//                if(tank_water_status == 1 && last_tank == 0) Log_Add("警报: 补水箱已空!");
//                last_tank = tank_water_status;

//                if(food_level_status == 1 && last_food == 0) Log_Add("警报: 鱼粮存量不足!");
//                last_food = food_level_status;

//                // --- 6. 区间防抖补水核心逻辑 (完美适配 没水=1, 有水=0) ---
//                
//                // [最高优先级]: 强制关阀条件
//                // 1. 水位碰到了高位浮球 (H变成0)
//                // 2. 补水箱没水了 (Tank变成1)
//                if(sensor_high_status == 0 || tank_water_status == 1) {
//                    if(filling_water == 1) {
//                        filling_water = 0;
//                        BSP_Relay_Set(DEV_WATER_VALVE, RELAY_OFF); // 关闭补水阀
//                        Log_Add(sensor_high_status == 0 ? "补水: 水满到达高位，停止" : "补水: 水箱缺水，强制关阀");
//                    }
//                }
//                // [次级优先级]: 开启补水条件
//                // 必须满足：低水位缺水(L=1) + 补水箱有水(Tank=0) + 高水位没触发(H=1)
//                else if(water_status == 1 && tank_water_status == 0 && sensor_high_status == 1) {
//                    if(filling_water == 0) {
//                        filling_water = 1;
//                        BSP_Relay_Set(DEV_WATER_VALVE, RELAY_ON); // 打开补水阀
//                        Log_Add("系统: 鱼缸缺水，开始自动补水...");
//                    }
//                }

//                // 7. 原有逻辑执行
//                heater_state = (water_status == 0 && temp_c < target_temp);
//                BSP_Relay_Set(DEV_HEATER, heater_state); 
//                
//                filter_running = (filter_mode == 1 || (filter_mode == 2 && (sys_tick_counter % 3600) < (filter_on_time * 60)));
//                BSP_Relay_Set(DEV_FILTER, filter_running);
//                
//                pump_running = (pump_mode == 1 || (pump_mode == 2 && (sys_tick_counter % (pump_pulse_sec * 2)) < pump_pulse_sec));
//                BSP_Relay_Set(DEV_PUMP, pump_running);
//                
//                // 8. 刷新本地鱼缸屏幕显示 (极速响应，不卡顿)
//                Update_Monitor_View(temp_c, voltage, purity); 
//                
//                // ?? 【终极优化】：组装现代化 JSON 格式并发给巴法云！
//                static int cloud_tick = 0; 
//                if(++cloud_tick >= 6) { 
//                    // 在 if(++cloud_tick >= 6) 里，替换整个 json_msg + cloud_data 部分
//char full_msg[300];
//sprintf(full_msg,
//    "#temp#:#%.1f#,#water#:#%d#,#food#:#%d#,#quality#:#%d#,#level#:#%s#,#heat#:#%s#,#filter#:#%s#,#oxy#:#%s#,#add#:#%s#\r\n",
//    temp_c,
//    tank_water_status,          // 0=有水 1=缺水
//    food_level_status,          // 0=充足 1=不足
//    purity,                     // 水质百分比
//    (water_status == 0 ? "正常" : "警告"),
//    (heater_state   ? "运行" : "停止"),
//    (filter_running ? "运行" : "停止"),
//    (pump_running   ? "运行" : "停止"),
//    (filling_water  ? "补水中" : "待机")
//);

//// 透传模式下直接发，不需要 cmd=2 包头
//HAL_UART_Transmit(&UART3_Handler, (u8*)full_msg, strlen(full_msg), 200);
//cloud_tick = 0; 
//                }
//                
//                idle_counter = 0;
//            }
//        }
//    }
//}


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sdram.h"
#include "lcd.h"
#include "touch.h"
#include "24cxx.h"
#include "adc.h"
#include "fish_tank_data.h"
#include "bsp_relay.h"
#include "bsp_ds18b20.h"
#include "bsp_liquid.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "text.h" 
#include "stm32f4xx_hal.h" 

// ==========================================
//  【配置区】
// ==========================================
#define RATIO_LEFT       0.44f
#define RATIO_RIGHT      0.56f
#define LAYOUT_GAP       10
#define LAYOUT_TOP_Y     40
#define LAYOUT_MAIN_H    520
#define DEFAULT_TARGET_TEMP  26.0f
#define LOG_MAX_HISTORY      300
#define FONT_SIZE_TITLE  24
#define FONT_SIZE_TEXT   16

#define COLOR_BG        0x1082 
#define COLOR_CARD      0x2124 
#define COLOR_ACCENT    0x051D 
#define COLOR_TEXT_V    0xAEBE 
#define COLOR_BTN_GRAY  0x7BEF 
#define COLOR_BTN_RED   0xF800 
#define COLOR_BTN_GRN   0x07E0 
#define COLOR_BTN_BLU   0x051F 
#define COLOR_BTN_FEED  0x07E0 
#define COLOR_GOOD      0x07E0 
#define COLOR_WARN      0xF800 
#define COLOR_SET_TEXT   0x07FF 
#define COLOR_SET_BORDER 0x07FF 
#define C_WHITE         0xFFFF

// --- [新增] 如果你的继电器只有4路，你需要为补水泵重新分配一个。这里暂时定义为4，请在bsp_relay.h中真实定义 ---
#ifndef DEV_REFILL_PUMP
#define DEV_REFILL_PUMP  4 
#endif

// 全局变量
float target_temp = DEFAULT_TARGET_TEMP;
float saved_temp_mirror = DEFAULT_TARGET_TEMP; // 温度镜像

// 其他参数的镜像
u8 saved_filter_mode = 1, saved_filter_on_time = 20;
u8 saved_pump_mode = 1, saved_pump_pulse_sec = 30;
u8 saved_feeder_mode = 2, saved_feeder_period_hours = 12;
u32 sys_tick_counter = 0; 

RTC_HandleTypeDef hrtc;
UART_HandleTypeDef UART3_Handler; // 这是专门给 WiFi 模块用的“对讲机”

u8 filter_mode = 1; u8 filter_on_time = 20; 
u8 pump_mode = 1; u8 pump_pulse_sec = 30; 
u8 feeder_mode = 2; u8 feeder_period_hours = 12; 
u32 last_feed_tick = 0; u8 feeding_state = 0; u8 feed_timer = 0;      
u8 water_status = 0; u8 heater_state = 0; u8 filter_running = 0; u8 pump_running = 0; 
u16 SCR_W = 800; u16 SCR_H = 480;

// --- [新增] 新传感器的全局状态变量 ---
u8 sensor_high_status = 0; // 鱼缸高水位状态
u8 tank_water_status = 0;  // 补水箱状态：0有水，1缺水
u8 food_level_status = 0;  // 鱼粮状态：0充足，1短缺
u8 filling_water = 0;      // 补水泵运行状态：0停止，1补水中

// 日志系统
int show_log_count = 3;   
char log_pool[LOG_MAX_HISTORY][120]; 
int log_total_count = 0;   
int log_view_offset = 0;   
short last_touch_y = -1;   

// 布局变量
u16 LEFT_CARD_W, RIGHT_CARD_W;
u16 LEFT_X, RIGHT_X;
u16 LOG_Y, LOG_W;
int LOG_H_DYNAMIC;
u16 UI_TEMP_Y, UI_FILTER_Y, UI_PUMP_Y, UI_FEEDER_Y;
u16 GAP_Y; 

#define BTN_W         62    
#define BTN_GAP       15    
#define BAR_H         36    
#define TOTAL_BAR_W   (BTN_W * 3 + BTN_GAP * 2) 

#define WIFI_SSID     "KIKI"
#define WIFI_PWD      "se4dr5ft6"
#define ATK_DEV_ID    "08719037788807742917"
#define ATK_DEV_PWD   "12345678"

// ==========================================
//  【巴法云配置区】
// ==========================================
#define BEMFA_UID   "8b1f4af3386240b7993525552354d55b" 
#define BEMFA_TOPIC "FishTank"  // 这里填你刚才新建的主题名字

// ==========================================
//  功能函数
// ==========================================
void Wipe_Area(u16 x, u16 y, u16 w, u16 h) {
    LCD_Fill(x, y, x + w, y + h, COLOR_CARD);
}


// 彻底统一的传感器初始化
void Extra_Sensors_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE(); // 开启 GPIOA 时钟

    // 1. PH2(鱼粮), PH3(补水箱)
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP; 
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
    
    // 2. [修改] 把 PA4(高位) 和 PA8(低位) 一起初始化！
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void App_Sync_Time(u8 year, u8 month, u8 date, u8 hour, u8 min, u8 sec) {
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    sTime.Hours = hour; sTime.Minutes = min; sTime.Seconds = sec;
    sDate.Year = year; sDate.Month = month; sDate.Date = date;
    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_Init_NoBattery(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
        HAL_RCC_OscConfig(&RCC_OscInitStruct);
        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    } else {
        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
    __HAL_RCC_RTC_ENABLE();

    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    HAL_RTC_Init(&hrtc);

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    char date_str[] = __DATE__; char time_str[] = __TIME__; 
    sTime.Hours = atoi(time_str); sTime.Minutes = atoi(&time_str[3]); sTime.Seconds = atoi(&time_str[6]);
    sDate.Year = atoi(&date_str[7]) - 2000;
    if(date_str[4] == ' ') sDate.Date = atoi(&date_str[5]); else sDate.Date = atoi(&date_str[4]);
    if(strncmp(date_str,"Jan",3)==0) sDate.Month=1; else if(strncmp(date_str,"Feb",3)==0) sDate.Month=2; 
    else if(strncmp(date_str,"Mar",3)==0) sDate.Month=3; else if(strncmp(date_str,"Apr",3)==0) sDate.Month=4; 
    else if(strncmp(date_str,"May",3)==0) sDate.Month=5; else if(strncmp(date_str,"Jun",3)==0) sDate.Month=6; 
    else if(strncmp(date_str,"Jul",3)==0) sDate.Month=7; else if(strncmp(date_str,"Aug",3)==0) sDate.Month=8; 
    else if(strncmp(date_str,"Sep",3)==0) sDate.Month=9; else if(strncmp(date_str,"Oct",3)==0) sDate.Month=10; 
    else if(strncmp(date_str,"Nov",3)==0) sDate.Month=11; else if(strncmp(date_str,"Dec",3)==0) sDate.Month=12;

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void Update_Log_UI(void) {
    int i;
    u16 lx = LAYOUT_GAP + 20; 
    u16 ly = LOG_Y + 45; 
    u16 text_width = LOG_W - 40; 
    show_log_count = (LOG_H_DYNAMIC - 50) / 20;
    if(show_log_count < 1) show_log_count = 1;
    Wipe_Area(lx, ly, text_width, show_log_count * 20);
    for(i=0; i<show_log_count; i++) {
        int pool_idx = log_view_offset + i;
        if(pool_idx < log_total_count) {
            BACK_COLOR = COLOR_CARD;
            if(log_view_offset == 0 && i == 0) POINT_COLOR = C_WHITE;
            else POINT_COLOR = COLOR_TEXT_V; 
            Show_Str(lx, ly + i*20, text_width, FONT_SIZE_TEXT, (u8*)log_pool[pool_idx], 16, 0);
        }
    }
    u16 bar_x = SCR_W - 15; u16 bar_h = show_log_count * 20;
    LCD_Fill(bar_x, ly, bar_x+3, ly + bar_h, COLOR_BG);
    if(log_total_count > show_log_count) {
        u16 slider_h = bar_h / (log_total_count/show_log_count + 1);
        if(slider_h < 10) slider_h = 10;
        float p = (float)log_view_offset / (log_total_count - show_log_count);
        u16 slider_y = ly + (u16)(p * (bar_h - slider_h));
        LCD_Fill(bar_x, slider_y, bar_x+3, slider_y + slider_h, COLOR_ACCENT);
    }
}

void Log_Add(char* text) {
    int i; char buf[120];
    RTC_TimeTypeDef sTime; RTC_DateTypeDef sDate;
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    
    sprintf(buf, "[%02d-%02d-%02d %02d:%02d:%02d] %s", 
            sDate.Year, sDate.Month, sDate.Date, 
            sTime.Hours, sTime.Minutes, sTime.Seconds, 
            text);
            
    for(i = LOG_MAX_HISTORY-1; i > 0; i--) strcpy(log_pool[i], log_pool[i-1]);
    strcpy(log_pool[0], buf);
    if(log_total_count < LOG_MAX_HISTORY) log_total_count++;
    log_view_offset = 0; 
    Update_Log_UI();
}

void Load_Settings(void) {
    u16 temp_int = (AT24CXX_ReadOneByte(0) << 8) | AT24CXX_ReadOneByte(1);
    if(temp_int > 400 || temp_int < 100) target_temp = DEFAULT_TARGET_TEMP; 
    else target_temp = (float)temp_int / 10.0f;
    
    filter_mode = AT24CXX_ReadOneByte(2); if(filter_mode>2) filter_mode=1;
    filter_on_time = AT24CXX_ReadOneByte(3); if(filter_on_time>60) filter_on_time=20;
    pump_mode = AT24CXX_ReadOneByte(4); if(pump_mode>2) pump_mode=1;
    pump_pulse_sec = AT24CXX_ReadOneByte(5); if(pump_pulse_sec>120) pump_pulse_sec=30;
    feeder_mode = AT24CXX_ReadOneByte(6); if(feeder_mode>2) feeder_mode=2;
    feeder_period_hours = AT24CXX_ReadOneByte(7); if(feeder_period_hours!=12 && feeder_period_hours!=24) feeder_period_hours=12;
    
    // 启动时同步所有镜像
    saved_temp_mirror = target_temp;
    saved_filter_mode = filter_mode; saved_filter_on_time = filter_on_time;
    saved_pump_mode = pump_mode; saved_pump_pulse_sec = pump_pulse_sec;
    saved_feeder_mode = feeder_mode; saved_feeder_period_hours = feeder_period_hours;
}

void Save_Settings(void) {
    // 只有发生改变时才写入，必须加入 5ms 物理写入等待时间，否则必丢数据！
    if(target_temp != saved_temp_mirror) {
        u16 temp_int = (u16)(target_temp * 10);
        AT24CXX_WriteOneByte(0, temp_int >> 8); delay_ms(5); 
        AT24CXX_WriteOneByte(1, temp_int & 0xFF); delay_ms(5);
        saved_temp_mirror = target_temp;
    }
    
    if(filter_mode != saved_filter_mode) { AT24CXX_WriteOneByte(2, filter_mode); delay_ms(5); saved_filter_mode = filter_mode; }
    if(filter_on_time != saved_filter_on_time) { AT24CXX_WriteOneByte(3, filter_on_time); delay_ms(5); saved_filter_on_time = filter_on_time; }
    
    if(pump_mode != saved_pump_mode) { AT24CXX_WriteOneByte(4, pump_mode); delay_ms(5); saved_pump_mode = pump_mode; }
    if(pump_pulse_sec != saved_pump_pulse_sec) { AT24CXX_WriteOneByte(5, pump_pulse_sec); delay_ms(5); saved_pump_pulse_sec = pump_pulse_sec; }
    
    if(feeder_mode != saved_feeder_mode) { AT24CXX_WriteOneByte(6, feeder_mode); delay_ms(5); saved_feeder_mode = feeder_mode; }
    if(feeder_period_hours != saved_feeder_period_hours) { AT24CXX_WriteOneByte(7, feeder_period_hours); delay_ms(5); saved_feeder_period_hours = feeder_period_hours; }
}

void Draw_CN_Btn(u16 x, u16 y, u16 w, u16 h, u16 color, char* text) {
    LCD_Fill(x, y, x + w, y + h, color);
    BACK_COLOR = color; POINT_COLOR = C_WHITE;
    u16 tx = x + (w - strlen(text)*8) / 2; u16 ty = y + (h - 16) / 2;
    Show_Str(tx, ty, w, 16, (u8*)text, 16, 0);
}

void Draw_Circle_Btn(u16 x, u16 y, u16 r, u16 color, char* symbol) {
    int i, j;
    for(i = x-r; i <= x+r; i++) {
        for(j = y-r; j <= y+r; j++) { if( (i-x)*(i-x) + (j-y)*(j-y) <= r*r ) LCD_Fast_DrawPoint(i, j, color); }
    }
    BACK_COLOR = color; POINT_COLOR = C_WHITE;
    LCD_ShowString(x-4, y-8, 50, 16, 16, (u8*)symbol); 
}

void Draw_CN_Setting_Frame(u16 btn_y, u8 mode, char* text) {
    u16 right_w = RIGHT_CARD_W - 20;
    u16 center_x = RIGHT_X + RIGHT_CARD_W / 2;
    u16 start_x = center_x - TOTAL_BAR_W / 2;
    u16 text_y = btn_y + BAR_H + 5; 
    Wipe_Area(RIGHT_X + 5, text_y - 5, right_w + 10, 32); 
    if(mode == 2) {
        POINT_COLOR = COLOR_SET_BORDER; LCD_DrawRectangle(start_x, text_y, start_x + TOTAL_BAR_W, text_y + 24);
        BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_SET_TEXT; 
        u16 tx = start_x + (TOTAL_BAR_W - strlen(text)*8) / 2;
        Show_Str(tx, text_y + 4, TOTAL_BAR_W, 16, (u8*)text, 16, 0);
    }
}

void Update_Filter_UI(void) {
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
    Show_Str(start_x, UI_FILTER_Y - 25, 200, 16, (u8*)"循环过滤系统", 16, 0);
    Draw_CN_Btn(start_x, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==1?COLOR_BTN_GRN:COLOR_BTN_GRAY), "开");
    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_FILTER_Y, BTN_W, BAR_H, (filter_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
    char buf[30]; sprintf(buf, "开启: %d 分钟/小时", filter_on_time); Draw_CN_Setting_Frame(UI_FILTER_Y, filter_mode, buf); 
}

void Update_Pump_UI(void) {
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
    Show_Str(start_x, UI_PUMP_Y - 25, 200, 16, (u8*)"增氧泵控制", 16, 0);
    Draw_CN_Btn(start_x, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==1?COLOR_BTN_GRN:COLOR_BTN_GRAY), "开");
    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_PUMP_Y, BTN_W, BAR_H, (pump_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
    char buf[30]; sprintf(buf, "周期: %d 秒/次", pump_pulse_sec); Draw_CN_Setting_Frame(UI_PUMP_Y, pump_mode, buf);
}

void Update_Feeder_UI(void) {
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V;
    Show_Str(start_x, UI_FEEDER_Y - 25, 200, 16, (u8*)"自动喂食机", 16, 0);
    Draw_CN_Btn(start_x, UI_FEEDER_Y, BTN_W, BAR_H, (feeder_mode==0?COLOR_BTN_RED:COLOR_BTN_GRAY), "停");
    u16 feed_btn_color = feeding_state ? COLOR_BTN_FEED : COLOR_BTN_GRAY;
    Draw_CN_Btn(start_x + BTN_W + BTN_GAP, UI_FEEDER_Y, BTN_W, BAR_H, feed_btn_color, (feeding_state?"...":"喂食"));
    Draw_CN_Btn(start_x + BTN_W*2 + BTN_GAP*2, UI_FEEDER_Y, BTN_W, BAR_H, (feeder_mode==2?COLOR_BTN_BLU:COLOR_BTN_GRAY), "自动");
    char buf[30]; sprintf(buf, "间隔: %d 小时", feeder_period_hours); Draw_CN_Setting_Frame(UI_FEEDER_Y, feeder_mode, buf);
}

// --- [修改] UI 监控视图，加入了补水箱和鱼粮的显示 ---
void Update_Monitor_View(float cur_temp, float voltage, int purity) {
    u16 lx = LEFT_X + 20; 
    u16 ly = LAYOUT_TOP_Y + 45; 
    u16 max_w = LEFT_CARD_W - 30; 
    char buf[50];
    Wipe_Area(lx, ly, max_w, 35); sprintf(buf, "%.1f", cur_temp);
    BACK_COLOR = COLOR_CARD; POINT_COLOR = C_WHITE; LCD_ShowString(lx, ly, 100, 32, 32, (u8*)buf);
    Show_Str(lx + 80, ly + 12, 50, 16, (u8*)"℃", 16, 0);
    
    // 加大擦除区域，防止文字重叠
    u16 y_cur = ly + 55; Wipe_Area(lx, y_cur, max_w, 300); 
    
    POINT_COLOR = (purity > 75 ? COLOR_GOOD : COLOR_WARN);
    sprintf(buf, "水质: %d%% (%.2fV)", purity, voltage); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
    
    // [修改这一行代码，把高低水位的 0和1 真实值打印出来]
    POINT_COLOR = (water_status==0?COLOR_GOOD:COLOR_WARN);
    sprintf(buf, "水位: %s (H:%d L:%d)", (water_status==0?"正常":"警告"), sensor_high_status, water_status); 
    Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
    
    // 新增：水箱和鱼粮状态
    POINT_COLOR = (tank_water_status==0 ? COLOR_GOOD : COLOR_WARN);
    sprintf(buf, "水箱: %s", (tank_water_status==0?"水量充足":"严重缺水")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

    POINT_COLOR = (food_level_status==0 ? COLOR_GOOD : COLOR_WARN);
    sprintf(buf, "鱼粮: %s", (food_level_status==0?"余量充足":"余量不足")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

    POINT_COLOR = COLOR_BTN_GRAY;
    sprintf(buf, "加热: %s", (heater_state?"开启":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
    sprintf(buf, "过滤: %s", (filter_running?"运行":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
    sprintf(buf, "增氧: %s", (pump_running?"运行":"停止")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;
    
    POINT_COLOR = filling_water ? COLOR_BTN_BLU : COLOR_BTN_GRAY;
    sprintf(buf, "补水: %s", (filling_water?"正在加水":"待机")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0); y_cur += 28;

    POINT_COLOR = feeding_state ? COLOR_BTN_FEED : COLOR_BTN_GRAY;
    sprintf(buf, "投食: %s", (feeding_state?"投放中":"待机")); Show_Str(lx, y_cur, max_w, 16, (u8*)buf, 16, 0);
}

void Update_Target_View(void) {
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; 
    char buf[20];
    Wipe_Area(center_x - 70, UI_TEMP_Y - 60, 140, 25); 
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V; 
    Show_Str(center_x - 48, UI_TEMP_Y - 55, 150, 16, (u8*)"目标温度设定", 16, 0);
    sprintf(buf, "%.1f", target_temp); 
    Wipe_Area(center_x - 30, UI_TEMP_Y - 10, 60, 30); 
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_ACCENT;
    Show_Str(center_x - 24, UI_TEMP_Y - 8, 100, 24, (u8*)buf, 24, 0); 
}

void Draw_Card(u16 x, u16 y, u16 w, u16 h, u8 *title) {
    LCD_Fill(x, y, x+w, y+h, COLOR_CARD); LCD_Fill(x, y, x+5, y+h, COLOR_ACCENT);
    BACK_COLOR = COLOR_CARD; POINT_COLOR = COLOR_TEXT_V; Show_Str(x+15, y+10, 200, FONT_SIZE_TITLE, title, 24, 0);
}

void Draw_Dashboard(void) {
    LCD_Clear(COLOR_BG); LCD_Fill(0, 0, SCR_W, 45, COLOR_ACCENT);
    BACK_COLOR = COLOR_ACCENT; POINT_COLOR = C_WHITE; Show_Str(20, 10, 450, 24, (u8*)"智能鱼缸监控终端 V38.0", 24, 0);
    
    Draw_Card(LEFT_X, LAYOUT_TOP_Y, LEFT_CARD_W, LAYOUT_MAIN_H, (u8*)"实时监控");
    Draw_Card(RIGHT_X, LAYOUT_TOP_Y, RIGHT_CARD_W, LAYOUT_MAIN_H, (u8*)"设备控制");
    if(LOG_H_DYNAMIC > 20) Draw_Card(LAYOUT_GAP, LOG_Y, LOG_W, LOG_H_DYNAMIC, (u8*)"系统运行日志"); 
    
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2;
    Draw_Circle_Btn(center_x - 65, UI_TEMP_Y, 22, COLOR_BTN_GRAY, "-");
    Draw_Circle_Btn(center_x + 65, UI_TEMP_Y, 22, COLOR_BTN_GRAY, "+");
    
    Update_Target_View();
}

// [新增] 初始化连接 WiFi 模块的串口3 (PB10=TX, PB11=RX)
void WiFi_Serial_Init(u32 baudrate) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    UART3_Handler.Instance = USART3;
    UART3_Handler.Init.BaudRate = baudrate;
    UART3_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART3_Handler.Init.StopBits = UART_STOPBITS_1;
    UART3_Handler.Init.Parity = UART_PARITY_NONE;
    UART3_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART3_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART3_Handler);
	
	
}



// [新增] 破冰测试：喊一句 AT，听听有没有 OK
void WiFi_Test_Communication(void) {
    char cmd[] = "AT\r\n";
    u8 rx_byte;
    u8 success = 0;
    int i;
    
    Log_Add("系统: 正在呼叫 WiFi 模块...");
    // 1. 发送暗号 "AT"
    HAL_UART_Transmit(&UART3_Handler, (u8*)cmd, strlen(cmd), 1000);
    
    // 2. 竖起耳朵听有没有回复 'O' 和 'K'
    for(i = 0; i < 100; i++) { 
        // 每次等 10 毫秒，最多等 100 次 (大约1秒)
        if(HAL_UART_Receive(&UART3_Handler, &rx_byte, 1, 10) == HAL_OK) {
            if(rx_byte == 'O') {
                success = 1; // 听到了大写的 O，基本就是 OK 了！
                break;
            }
        }
    }
    
    // 3. 把结果打在屏幕上
    if(success) {
        Log_Add("成功: WiFi 模块已回答 OK！");
    } else {
        Log_Add("失败: WiFi 模块装死无响应...");
    }
}

// 发送AT指令并等待响应
// 返回值: 1 成功; 0 失败
u8 WiFi_Send_Cmd(char *cmd, char *ack, u32 timeout)
{
    u8 len = 0;
    char rx_buf[256] = {0};
    
    // 1. 清空串口3接收缓冲区 (假设你已经有了串口接收中断或缓存)
    // 这里简单处理：发送前先清空单片机的接收缓存
    memset(rx_buf, 0, 256); 
    
    // 2. 发送指令
    HAL_UART_Transmit(&UART3_Handler, (u8*)cmd, strlen(cmd), 100);
    
    // 3. 循环等待响应
    u32 t = 0;
    while(t < timeout)
    {
        // 建议在串口3中断里把数据存入一个全局缓冲区，这里检查该缓冲区
        // 临时方案：直接轮询接收（不推荐，但如果你没写中断逻辑可以用这个）
        u8 res;
        if(HAL_UART_Receive(&UART3_Handler, &res, 1, 10) == HAL_OK)
        {
            if(len < 250) rx_buf[len++] = res;
            if(strstr(rx_buf, ack)) return 1; // 查到了预期的回复
        }
        t += 10;
        
    }
    return 0; // 超时没收到回复
}

// 工业级 AT 雷达 (光速无睡版，专治漏字！)
u8 Send_AT(char* cmd, char* ack, u32 timeout_ms) {
    char buf[250] = {0};
    int len = 0;
    uint32_t tmp;
    uint32_t start_time = HAL_GetTick(); // 记录开始时间，用作超时判断
    
    // 1. 发送前暴力清空所有残留和报错
    tmp = USART3->SR; tmp = USART3->DR; (void)tmp;
    
    // 2. 发送指令
    if(cmd != NULL) {
        for(int i = 0; i < strlen(cmd); i++) {
            USART3->DR = cmd[i]; 
            // 等待发送时，也顺手吸干进来的回音
            while((USART3->SR & (1<<7)) == 0) { 
                if(USART3->SR & (1<<5)) { 
                    char rx = USART3->DR; 
                    if(rx >= 0x20 && rx <= 0x7E && len < 100) buf[len++] = rx;
                }
            }
        }
    }
    
    // 3. 极速扫描期（?? 里面绝对没有 delay 睡觉代码！）
    while((HAL_GetTick() - start_time) < timeout_ms) {
        // 只要听到声音，瞬间吸干！
        if(USART3->SR & (1<<5)) { 
            char rx = USART3->DR;
            if(rx >= 0x20 && rx <= 0x7E && len < 240) buf[len++] = rx;
            
            // 只要凑齐了暗号(比如 OK)，直接凯旋！
            if(strstr(buf, ack) != NULL) return 1; 
        }
        
        // 终极保命：如果万一发生溢出(ORE标志)，立刻清空恢复！
        if(USART3->SR & (1<<3)) { 
            tmp = USART3->SR; tmp = USART3->DR; (void)tmp; 
        }
    }
    
    // 4. 打印遗言
    if(len > 0) { 
        buf[len] = '\0'; 
        char log[120];
        sprintf(log, "回话: %s", buf);
        Log_Add(log); 
    } else {
        Log_Add("回话: [死寂无声]");
    }
    return 0; 
}

// [巴法云专属] 现代化 TCP 连云程序 (严格状态机时序版)
void WiFi_Connect_Bemfa(void) {
    Log_Add("系统: 准备连接巴法云 TCP 创客云...");
    delay_ms(2500); 
    
    Log_Add("系统: 1. 测试指令通道...");
    if(!Send_AT("AT\r\n", "OK", 1000)) { Log_Add("严重: 模块通讯失败！"); return; }
    
    Log_Add("系统: 1.5 初始化网络规矩...");
    Send_AT("ATE0\r\n", "OK", 1000); 
    Send_AT("AT+CWMODE=1\r\n", "OK", 1000);
    Send_AT("AT+CIPMUX=0\r\n", "OK", 1000);  // 单连接模式 (透传的先决条件)
    // ?? 注意：这里删除了提前开启透传的错误指令！
    
    Log_Add("系统: 2. 连接 KIKI 热点(20秒)...");
    if(Send_AT("AT+CWJAP=\"KIKI\",\"se4dr5ft6\"\r\n", "OK", 20000)) {
        Log_Add("-> 热点接入！强制等待分配IP...");
        delay_ms(3000); 
    } else {
        Log_Add("-> 热点连接失败！"); return;
    }
    

    Log_Add("系统: 3. 正在敲击巴法云大门...");
    // 顺理成章地发起 TCP 连接
    if(Send_AT("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r\n", "CONNECT", 10000)) {
        Log_Add("-> TCP 握手成功！");
    } else {
        Log_Add("-> 服务器连接失败！"); return;
    }

    Log_Add("系统: 4. 开启透传通道...");
    // ?? 核心修正：必须在 CONNECT 成功之后，才能开启透传！
    Send_AT("AT+CIPMODE=1\r\n", "OK", 1000); 
    Send_AT("AT+CIPSEND\r\n", ">", 1000); // 看到 > 符号代表通道已敞开

    Log_Add("系统: 5. 发送设备上线报文...");
    char sub_cmd[100];
    sprintf(sub_cmd, "cmd=1&uid=%s&topic=%s\r\n", BEMFA_UID, BEMFA_TOPIC);
    HAL_UART_Transmit(&UART3_Handler, (u8*)sub_cmd, strlen(sub_cmd), 500);
    
    delay_ms(1000);
    Log_Add("==== 大满贯！巴法云通道已打开 ====");
}


// ==========================================
//  6. Main 函数
// ==========================================
int main(void) {
    short raw_temp; float temp_c; u16 adcx; float voltage; int purity;
    int one_sec_counter = 0, idle_counter = 0; 
    HAL_Init(); Stm32_Clock_Init(360, 25, 2, 8); delay_init(180); uart_init(115200);
    BSP_Relay_Init(); BSP_Liquid_Init(); AT24CXX_Init(); SDRAM_Init(); LCD_Init(); tp_dev.init(); MY_ADC_Init(); 
    
    Extra_Sensors_Init(); // --- [新增] 初始化报警与补水传感器 ---

    RTC_Init_NoBattery(); 
    font_init(); 
    
    SCR_W = lcddev.width; SCR_H = lcddev.height; 
    if(SCR_W == 0) { SCR_W = 800; SCR_H = 480; } 
    
    LEFT_CARD_W = (SCR_W - 3 * LAYOUT_GAP) * RATIO_LEFT;
    RIGHT_CARD_W = (SCR_W - 3 * LAYOUT_GAP) * RATIO_RIGHT;
    LEFT_X = LAYOUT_GAP;
    RIGHT_X = LEFT_X + LEFT_CARD_W + LAYOUT_GAP;
    LOG_Y = LAYOUT_TOP_Y + LAYOUT_MAIN_H + LAYOUT_GAP;
    LOG_H_DYNAMIC = SCR_H - LOG_Y - 5; if(LOG_H_DYNAMIC < 50) LOG_H_DYNAMIC = 50; 
    LOG_W = SCR_W - LAYOUT_GAP * 2;
    
    UI_TEMP_Y = LAYOUT_TOP_Y + 110;   // 下移20
    UI_FILTER_Y = LAYOUT_TOP_Y + 175; // 下移20
    GAP_Y = 105;                      // 间距收缩
    UI_PUMP_Y = UI_FILTER_Y + GAP_Y;
    UI_FEEDER_Y = UI_PUMP_Y + GAP_Y;
    
    Load_Settings(); Draw_Dashboard(); 
    Update_Filter_UI(); Update_Pump_UI(); Update_Feeder_UI(); 
    Log_Add("系统启动就绪..."); Log_Add("报警系统已挂载..."); 
	
	// --- 修改这里 ---
    WiFi_Serial_Init(115200); 
    WiFi_Connect_Bemfa(); // 调用上面写的逻辑
    // ----------------
    // ---------------------------------------------------

    while(DS18B20_Init()) delay_ms(500); // 这行及以后的代码暂时不会跑了
    u16 center_x = RIGHT_X + RIGHT_CARD_W/2; u16 start_x = center_x - TOTAL_BAR_W/2;

    while(1) {
        tp_dev.scan(0);
        if(tp_dev.sta & TP_PRES_DOWN) {
            u16 x = tp_dev.x[0]; u16 y = tp_dev.y[0]; idle_counter = 0;
            
            if(y > (UI_TEMP_Y-40) && y < (UI_TEMP_Y+40)) {
                if(x > center_x-90 && x < center_x-40) { target_temp -= 0.5f; Update_Target_View(); delay_ms(100); }
                else if(x > center_x+40 && x < center_x+90) { target_temp += 0.5f; Update_Target_View(); delay_ms(100); }
            }
            else if(y > LOG_Y && y < LOG_Y + LOG_H_DYNAMIC) {
                if(last_touch_y != -1) {
                    short delta = y - last_touch_y;
                    if(delta < -10) { if(log_view_offset < log_total_count - show_log_count) { log_view_offset++; Update_Log_UI(); } last_touch_y = y; }
                    else if(delta > 10) { if(log_view_offset > 0) { log_view_offset--; Update_Log_UI(); } last_touch_y = y; }
                } else { last_touch_y = y; }
            }
            else if(y > UI_FILTER_Y && y < UI_FILTER_Y + BAR_H) {
                if(x > start_x && x < start_x + BTN_W) { if(filter_mode!=0){filter_mode=0; Log_Add("过滤: 停止");} }
                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) { if(filter_mode!=1){filter_mode=1; Log_Add("过滤: 开启");} }
                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(filter_mode!=2){filter_mode=2; Log_Add("过滤: 自动模式");} }
                Update_Filter_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
            }
            else if(filter_mode == 2 && y > UI_FILTER_Y+BAR_H && y < UI_FILTER_Y+BAR_H+36) {
                filter_on_time += 5; if(filter_on_time > 60) filter_on_time = 5; Update_Filter_UI(); delay_ms(150);
            }
            else if(y > UI_PUMP_Y && y < UI_PUMP_Y+BAR_H) {
                if(x > start_x && x < start_x + BTN_W) { if(pump_mode!=0){pump_mode=0; Log_Add("增氧: 停止");} }
                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) { if(pump_mode!=1){pump_mode=1; Log_Add("增氧: 开启");} }
                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(pump_mode!=2){pump_mode=2; Log_Add("增氧: 自动模式");} }
                Update_Pump_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
            }
            else if(pump_mode == 2 && y > UI_PUMP_Y+BAR_H && y < UI_PUMP_Y+BAR_H+36) {
                pump_pulse_sec = (pump_pulse_sec==30?60:30); Update_Pump_UI(); delay_ms(150);
            }
            else if(y > UI_FEEDER_Y && y < UI_FEEDER_Y+BAR_H) {
                if(x > start_x && x < start_x+BTN_W) { if(feeder_mode!=0){feeder_mode=0; Log_Add("投食: 禁用");} }
                else if(x > start_x+BTN_W+BTN_GAP && x < start_x+BTN_W*2+BTN_GAP) {
                    if(!feeding_state) { Log_Add("手动投食启动"); BSP_Relay_Set(DEV_FEEDER, RELAY_ON); feeding_state = 1; feed_timer = 3; Update_Feeder_UI(); }
                }
                else if(x > start_x+BTN_W*2+BTN_GAP*2 && x < start_x+TOTAL_BAR_W) { if(feeder_mode!=2){feeder_mode=2; Log_Add("投食: 自动模式");} }
                Update_Feeder_UI(); while(tp_dev.sta & TP_PRES_DOWN) tp_dev.scan(0);
            }
            else if(feeder_mode == 2 && y > UI_FEEDER_Y+BAR_H && y < UI_FEEDER_Y+BAR_H+36) {
                feeder_period_hours = (feeder_period_hours==12? 24 : 12); Update_Feeder_UI(); delay_ms(150);
            }
        } else {
            last_touch_y = -1; 
            delay_ms(10);
            if(++one_sec_counter >= 100) {
                sys_tick_counter++; one_sec_counter = 0;
                if(feeding_state && --feed_timer == 0) { BSP_Relay_Set(DEV_FEEDER, RELAY_OFF); feeding_state = 0; Log_Add("投食执行完毕"); Update_Feeder_UI(); }
                if(feeder_mode == 2 && feeding_state == 0) {
                    u32 interval = (feeder_period_hours == 12) ? 43200 : 86400; 
                    if(sys_tick_counter - last_feed_tick >= interval) {
                        BSP_Relay_Set(DEV_FEEDER, RELAY_ON); feeding_state = 1; feed_timer = 3; last_feed_tick = sys_tick_counter; Log_Add("自动投食开启"); Update_Feeder_UI(); 
                    }
                }
            }
            // ==========================================
            //  核心传感器轮询与逻辑处理 (约 500ms 一次)
            // ==========================================
            if(++idle_counter > 50) {
                Save_Settings(); 
                
                // --- 彻底抛弃 BSP_Liquid_Read，统一使用底层读取 ---
                static u8 last_water = 0;
                
                // 1. 连续读取 4 个传感器的真实物理状态
                water_status       = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8); // 鱼缸低位 (PA8)
                sensor_high_status = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4); // 鱼缸高位
                tank_water_status  = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_3); // 补水箱 (PH3)
                food_level_status  = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_2); // 鱼粮 (PH2)
                
                // 3. 温度读取 (带滤波防错)
                short temp_new = DS18B20_Get_Temp(); 
                if(temp_new != 0 && temp_new != 850) {
                    raw_temp = temp_new;
                    temp_c = raw_temp / 10.0f;
                }
                
                // 4. 水质读取
                adcx = Get_Adc_Average(ADC_CHANNEL_5, 10); 
                voltage = (float)adcx * (3.3f / 4096.0f);
                purity = (voltage > 3.2f) ? 100 : (int)((voltage / 3.2f) * 100);
                
                // --- 5. 报警判定 ---
                static u8 last_tank = 0, last_food = 0;
                
                if(water_status == 1 && last_water == 0) Log_Add("警报: 鱼缸水位过低!");
                else if(water_status == 0 && last_water == 1) Log_Add("提示: 鱼缸水位已恢复.");
                last_water = water_status;

                if(tank_water_status == 1 && last_tank == 0) Log_Add("警报: 补水箱已空!");
                last_tank = tank_water_status;

                if(food_level_status == 1 && last_food == 0) Log_Add("警报: 鱼粮存量不足!");
                last_food = food_level_status;

                // --- 6. 区间防抖补水核心逻辑 (完美适配 没水=1, 有水=0) ---
                
                // [最高优先级]: 强制关阀条件
                // 1. 水位碰到了高位浮球 (H变成0)
                // 2. 补水箱没水了 (Tank变成1)
                if(sensor_high_status == 0 || tank_water_status == 1) {
                    if(filling_water == 1) {
                        filling_water = 0;
                        BSP_Relay_Set(DEV_WATER_VALVE, RELAY_OFF); // 关闭补水阀
                        Log_Add(sensor_high_status == 0 ? "补水: 水满到达高位，停止" : "补水: 水箱缺水，强制关阀");
                    }
                }
                // [次级优先级]: 开启补水条件
                // 必须满足：低水位缺水(L=1) + 补水箱有水(Tank=0) + 高水位没触发(H=1)
                else if(water_status == 1 && tank_water_status == 0 && sensor_high_status == 1) {
                    if(filling_water == 0) {
                        filling_water = 1;
                        BSP_Relay_Set(DEV_WATER_VALVE, RELAY_ON); // 打开补水阀
                        Log_Add("系统: 鱼缸缺水，开始自动补水...");
                    }
                }

                // 7. 原有逻辑执行
                heater_state = (water_status == 0 && temp_c < target_temp);
                BSP_Relay_Set(DEV_HEATER, heater_state); 
                
                filter_running = (filter_mode == 1 || (filter_mode == 2 && (sys_tick_counter % 3600) < (filter_on_time * 60)));
                BSP_Relay_Set(DEV_FILTER, filter_running);
                
                pump_running = (pump_mode == 1 || (pump_mode == 2 && (sys_tick_counter % (pump_pulse_sec * 2)) < pump_pulse_sec));
                BSP_Relay_Set(DEV_PUMP, pump_running);
                
                // 8. 刷新本地鱼缸屏幕显示 (极速响应，不卡顿)
                Update_Monitor_View(temp_c, voltage, purity); 
                
                // ?? 【终极优化】：组装现代化 JSON 格式并发给巴法云！
                static int cloud_tick = 0; 
                if(++cloud_tick >= 6) { 
                    char json_msg[100];
                    // ?? 终极绝杀：彻底抛弃标准的双引号 JSON！用井号代替！巴法云绝对不会拦截这个！
                    sprintf(json_msg, "{#temp#:#%.1f#,#water#:#%d#,#food#:#%d#}", 
                            temp_c, tank_water_status, food_level_status);
                    
                    char cloud_data[200];
                    sprintf(cloud_data, "cmd=2&uid=%s&topic=%s&msg=%s\r\n", 
                            BEMFA_UID, BEMFA_TOPIC, json_msg);
                    
                    HAL_UART_Transmit(&UART3_Handler, (u8*)cloud_data, strlen(cloud_data), 100);
                    cloud_tick = 0; 
                }
                
                idle_counter = 0;
            }
        }
    }
}

