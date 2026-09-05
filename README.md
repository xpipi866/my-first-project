# 基于GRU的交通流量预测与拥堵分析

使用 GRU（门控循环单元）对城市路段交通流量进行时序预测，并识别未来潜在拥堵时段。


## 📌 项目简介

本项目针对城市路段交通流数据，完成从数据清洗、特征工程、模型训练到未来流量预测的全流程实现。核心思路是将交通流量视为时间序列，利用 GRU 捕获其日周期性和长短期依赖规律。

### 主要特点
- 支持多路段独立建模与预测
- 自动解析时间字段，提取小时、星期等周期性特征（正余弦编码）
- 构建滑动窗口序列数据集，支持自定义历史时间步长度
- 双层 GRU + Dropout + EarlyStopping 防过拟合
- 输出未来 24 小时（96 个时间步）滚动预测
- 基于历史均值的拥堵判别逻辑
- 自动生成训练曲线、预测对比图、拥堵时段分布图


## 🗂️ 数据集说明

- **数据来源**：4 条城市路段的交通流检测器记录
- **记录条数**：10,000+ 条
- **时间粒度**：每 15 分钟一条记录
- **关键字段**：
  - `Site Name`：路段名称
  - `Report Date`：报告日期
  - `Time Period Ending`：时段结束时间
  - `Avg mph`：平均车速（mph）
  - `Total Volume`：总车流量

> 注：各路段检测器相互独立，未提供路段间的拓扑连接关系，因此本项目采用纯时序建模方案。


## 🧠 模型架构

```
Input(sequence_length, n_features)
       ↓
    GRU(units=50, return_sequences=True)
       ↓
      Dropout(0.2)
       ↓
    GRU(units=50, return_sequences=False)
       ↓
      Dropout(0.2)
       ↓
    Dense(units=1)
```

- **优化器**：Adam
- **损失函数**：均方误差（MSE）
- **评估指标**：RMSE、MAE、R²


## 📊 实验结果

| 路段 | RMSE | MAE | R² |
|:---|:---|:---|:---|
| 路段 A | — | — | 0.97 |




## 📁 项目结构

```
.
├── data/                          # 原始数据 CSV 文件
├── model_outputs/                 # 输出目录（自动创建）
│   ├── * _loss_plot.png           # 训练损失曲线
│   ├── * _prediction_comparison.png # 预测对比图
│   └── * _hourly_congestion.png   # 拥堵小时分布
├── traffic_prediction.py          # 主程序
├── requirements.txt               # 依赖库
└── README.md
```


## ⚙️ 环境依赖

- Python 3.8+
- TensorFlow 2.x
- pandas / numpy
- scikit-learn
- matplotlib

安装依赖：
```bash
pip install -r requirements.txt
```


## 🚀 快速开始

### 1. 准备数据
将 CSV 文件放入项目根目录，或修改代码中 `file_names` 列表指向正确路径。

### 2. 调整配置（可选）
```python
sequence_length = 24          # 用过去24个点（6小时）预测下一点
future_prediction_steps = 96  # 预测未来96个点（24小时）
```

### 3. 运行程序
```bash
python traffic_prediction.py
```

### 4. 查看结果
所有输出（模型指标、图表）保存在 `model_outputs/` 目录下。


## 🔮 预测逻辑

1. 模型训练完成后，取出最后一个时间窗口作为初始输入
2. 循环执行单步预测 → 更新输入窗口，逐点生成未来流量
3. 每步预测时同步计算时间特征（小时正余弦、星期正余弦）
4. 将预测值与历史平均流量对比，判定是否拥堵


## 📈 输出图表

运行后自动生成以下图表：

| 图表 | 说明 |
|:---|:---|
| `*_loss_plot.png` | 训练损失曲线，展示模型收敛情况 |
| `*_prediction_comparison.png` | 真实值 vs 预测值对比 |
| `*_hourly_congestion.png` | 历史拥堵发生的小时频次分布 |


## 🔧 待改进方向

- [ ] 将平均车速纳入输入特征，实现多变量时序预测
- [ ] 将多条路段整合为多输出模型，一次预测全部路段
- [ ] 增加 LSTM 或 XGBoost 作为对比基线
- [ ] 若获取路段拓扑信息，升级为 STGCN 等时空图网络


## 📝 备注

- 本项目为**课程设计**作品，主要用于功能验证
- 数据来自 4 条独立路段，未使用路网拓扑信息
- R² = 0.97 为单路段结果，具体数值因路段而异


## 📧 联系方式

如有问题，欢迎通过 GitHub Issues 联系。
