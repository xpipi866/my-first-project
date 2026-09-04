#ifndef __FISH_TANK_DATA_H
#define __FISH_TANK_DATA_H

#include "stdint.h"

// --- 1. 用户设置数据 (需要存入 EEPROM) ---
typedef struct {
    float target_temp;         // 目标温度 (例如: 26.5)
    uint16_t feed_interval_hr; // 喂食间隔 (例如: 每 12 小时)
    uint8_t light_on_hour;     // 开灯时间 (例如: 8 点)
    uint8_t light_off_hour;    // 关灯时间 (例如: 20 点)
    uint32_t checksum;         // 校验位，用于判断数据是否有效
} Tank_Settings_t;

// --- 2. 实时状态数据 (不需要保存) ---
typedef struct {
    float current_temp;        // 当前水温
    uint8_t water_level_ok;    // 水位是否正常 (1:正常 0:缺水)
    
    // 继电器当前状态 (0:关 1:开)
    uint8_t relay_heater;
    uint8_t relay_filter;
    uint8_t relay_feeder;
    uint8_t relay_oxygen;
    
    // 系统运行时间
    uint32_t last_feed_timestamp; // 上次喂食的时间
} Tank_Status_t;

// --- 3. 全局变量声明 ---
extern Tank_Settings_t g_UserSet; // 用户设置
extern Tank_Status_t   g_DeviceStatus; // 设备状态

#endif