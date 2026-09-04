#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H

// ==========================================
//  1. 时间配置
// ==========================================
// 1 = 自动同步编译时间, 0 = 使用自定义时间
#define USE_AUTO_COMPILE_TIME  1  

#define CFG_START_YEAR   2024
#define CFG_START_MONTH  5
#define CFG_START_DAY    20
#define CFG_START_HOUR   12
#define CFG_START_MIN    0
#define CFG_START_SEC    0

// ==========================================
//  2. 屏幕布局配置 (V27.0 黄金比例版)
// ==========================================
#define LAYOUT_GAP       10
#define LAYOUT_TOP_Y     40
#define LAYOUT_MAIN_H    520   // 主卡片高度

// [关键修改] 左右分栏比例调整
// 左侧扩大到 44%，右侧缩小到 56%
#define RATIO_LEFT       0.44f
#define RATIO_RIGHT      0.56f

// 字体大小
#define FONT_SIZE_TITLE  24
#define FONT_SIZE_TEXT   16

// ==========================================
//  3. 设备默认参数
// ==========================================
#define DEFAULT_TARGET_TEMP  26.0f
#define LOG_MAX_HISTORY      300

#endif