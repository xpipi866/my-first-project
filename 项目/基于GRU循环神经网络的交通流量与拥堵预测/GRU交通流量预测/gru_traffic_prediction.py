import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import GRU, Dense, Dropout, Input
from tensorflow.keras.optimizers import Adam
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.callbacks import EarlyStopping
import os
import math  # 导入 math 模块用于数学运算

# 设置绘图风格与中文显示
plt.style.use('ggplot')
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用于正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用于正常显示负号

# 创建输出目录
output_dir = "model_outputs"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# 定义要处理的文件列表
file_names = [
    #"6acd703f14db6b7b4d3105dcb98d8511_becd84a938487f997d66e0c43332692a_8.csv",
     "7fd7ff74f7f0d135f5638eb1d74f529a_b9330e29efa34ede0d898b27c9ce044a_8.csv",
    # "93237b4c32c86b8ff4d8e33f8db77524_0036f8fc984c6011af2570bf03406cc5_8.csv",
    # "c4eca4f4b2f2ed18f3456bec693ff834_a1c36fd8766622d043376717f18b8351_8.csv"
]

#--------------------------------------------------------------------------------
print("--- 1. 数据加载与预处理 ---")
road_data = {}  # 存储处理后的每个路段的数据

for fname in file_names:
    print(f"\n尝试加载文件: {fname}")
    try:
        # 1. 加载CSV文件
        df = pd.read_csv(fname)
        print(f"原始文件 '{fname}' 加载成功。前5行数据:")
        print(df.head())
        print(f"原始数据信息:")
        df.info()

        # 2. 检查必要列是否存在
        required_cols = ['Site Name', 'Report Date', 'Time Period Ending', 'Avg mph', 'Total Volume']
        if not all(col in df.columns for col in required_cols):
            print(f"文件 {fname} 缺少必要的列。跳过处理。所需列: {required_cols}")
            print(f"实际列名: {df.columns.tolist()}")
            continue

        # 3. 解析日期时间数据
        df['date_part'] = pd.to_datetime(df['Report Date'], format='%d/%m/%Y %H:%M:%S', errors='coerce', dayfirst=True).dt.normalize()
        df['time_delta_part'] = pd.to_timedelta(df['Time Period Ending'], errors='coerce')
        df['测量时间'] = df['date_part'] + df['time_delta_part']

        # 打印调试信息
        print(f"DEBUG: 'Report Date' parsed to date_part (first 5):")
        print(df['date_part'].head())
        num_nat_date_part = df['date_part'].isnull().sum()
        print(f"DEBUG: Number of NaT values in 'date_part': {num_nat_date_part}")
        if num_nat_date_part > 0:
            print(f"  **注意: 'Report Date' 列有 {num_nat_date_part} 个值未能正确解析。**")
            print("  **请检查原始CSV文件中这些日期的格式是否一致。**")
            print("  **未能解析的 'Report Date' 示例 (前5个):")
            print(df[df['date_part'].isnull()]['Report Date'].head())

        print(f"DEBUG: 'Time Period Ending' parsed to time_delta_part (first 5):")
        print(df['time_delta_part'].head())
        print(f"DEBUG: Number of NaT values in 'time_delta_part': {df['time_delta_part'].isnull().sum()}")
        print(f"DEBUG: '测量时间' combined (first 5):")
        print(df['测量时间'].head())
        print(f"DEBUG: Number of NaT values in '测量时间': {df['测量时间'].isnull().sum()}")

        # 4. 清理临时列并处理缺失值
        df.drop(columns=['date_part', 'time_delta_part'], inplace=True)
        initial_rows_after_datetime = len(df)
        df.dropna(subset=['测量时间'], inplace=True)
        if len(df) < initial_rows_after_datetime:
            print(f" 注意: 移除了 {initial_rows_after_datetime - len(df)} 行，因为 '测量时间' 解析失败。")
        print(f"日期时间解析后剩余数据量: {len(df)}")

        # 5. 重命名列
        df = df.rename(columns={
            'Site Name': '路段名称',
            'Avg mph': '平均车速',
            'Total Volume': '总车数'
        })
        print(f"列重命名后，数据前5行:")
        print(df.head())

        # 6. 处理数值列缺失值
        initial_rows_before_dropna = len(df)
        df.dropna(subset=['平均车速', '总车数'], inplace=True)
        if len(df) < initial_rows_before_dropna:
            print(f" 注意: 移除了 {initial_rows_before_dropna - len(df)} 行，因为数值列存在缺失值。")
        print(f"处理后剩余数据量: {len(df)}")

        # 7. 规范化路段名称并存储
        if not df.empty:
            road_name = df['路段名称'].iloc[0]
            sanitized_road_name = road_name.replace('/', '_').replace('\\', '_')
            df = df.sort_values(by='测量时间').reset_index(drop=True)
            road_data[sanitized_road_name] = df
            print(f"成功加载并处理路段: {road_name}，数据量: {len(df)} 条")
        else:
            print(f"文件 {fname} 处理后无有效数据，跳过处理。")

    except FileNotFoundError:
        print(f"错误: 文件 '{fname}' 未找到。请检查文件路径和名称。")
        print(f"当前工作目录: {os.getcwd()}")
    except Exception as e:
        print(f"处理文件 {fname} 时发生错误: {e}")

# 检查是否加载了数据
if not road_data:
    print("\n------------------------------------------------------")
    print("没有成功加载任何路段数据。程序将退出。")
    print("请检查：")
    print("1. CSV文件是否存在或路径是否正确。")
    print("2. 列名是否与代码要求一致。")
    print("3. 日期时间格式是否匹配。")
    print("4. 数值列是否存在大量缺失值。")
    print("------------------------------------------------------")
    exit()
#----------------------------------------------------------------------------
# 定义序列创建函数（多输入特征，单输出目标）
def create_sequences_new(features_data, target_data, seq_length):
    X, y = [], []
    for i in range(len(features_data) - seq_length):
        X.append(features_data[i:(i + seq_length)])
        y.append(target_data[i + seq_length])
    return np.array(X), np.array(y)

# 初始化模型和缩放器存储
models = {}
flow_scalers = {}
sequence_length = 24  # 使用过去24个时间点（6小时）进行预测
future_prediction_steps = 96  # 预测未来24小时（96个15分钟时间步）
congestion_analysis = {}  # 存储拥堵分析结果
#-----------------------------------------------------------------------------------------
for road_name_original, df in road_data.items():
    road_name_for_filename = road_name_original.replace('/', '_').replace('\\', '_')
    print(f"\n--- 处理路段: {road_name_original} ---")
    tf.keras.backend.clear_session()

    # 1. 添加时间特征（小时、星期几及其循环编码）
    df['hour'] = df['测量时间'].dt.hour
    df['dayofweek'] = df['测量时间'].dt.dayofweek
    df['hour_sin'] = np.sin(2 * math.pi * df['hour'] / 24)
    df['hour_cos'] = np.cos(2 * math.pi * df['hour'] / 24)
    df['dayofweek_sin'] = np.sin(2 * math.pi * df['dayofweek'] / 7)
    df['dayofweek_cos'] = np.cos(2 * math.pi * df['dayofweek'] / 7)

    # 2. 分离流量数据和时间特征
    flow_data = df[['总车数']].values
    time_features = df[['hour_sin', 'hour_cos', 'dayofweek_sin', 'dayofweek_cos']].values

    # 3. 流量数据标准化
    flow_scaler = MinMaxScaler(feature_range=(0, 1))
    scaled_flow_data = flow_scaler.fit_transform(flow_data)
    flow_scalers[road_name_original] = flow_scaler

    # 4. 组合输入特征（缩放流量+时间特征）
    features_for_model = np.concatenate((scaled_flow_data, time_features), axis=1)
    target = scaled_flow_data

    # 5. 创建序列数据
    X, y = create_sequences_new(features_for_model, target, sequence_length)
    if len(X) == 0:
        print(f"路段数据量不足，跳过。")
        continue

    # 6. 划分训练集和测试集
    train_size = int(len(X) * 0.8)
    X_train, X_test = X[:train_size], X[train_size:]
    y_train, y_test = y[:train_size], y[train_size:]

    # 7. 重塑数据以适应GRU输入格式
    X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], X_train.shape[2]))
    X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], X_test.shape[2]))

    # 8. 构建GRU模型
    print(f"--- 2. 为 {road_name_original} 构建GRU模型 ---")
    model = Sequential([
        Input(shape=(X_train.shape[1], X_train.shape[2])),
        GRU(units=50, return_sequences=True),
        Dropout(0.2),
        GRU(units=50, return_sequences=False),
        Dropout(0.2),
        Dense(units=1)
    ])
    model.compile(optimizer='adam', loss='mean_squared_error')

    # 9. 训练模型（带早停策略）
    print(f"--- 3. 训练 {road_name_original} 的GRU模型 ---")
    early_stopping = EarlyStopping(
        monitor='val_loss',
        patience=10,
        mode='min',
        restore_best_weights=True
    )
    history = model.fit(
        X_train, y_train,
        epochs=50,
        batch_size=4,
        validation_split=0.1,
        verbose=1,
        callbacks=[early_stopping]
    )
    models[road_name_original] = model

    # 10. 模型评估
    y_pred_scaled = model.predict(X_test, verbose=0)
    y_test_inverse = flow_scaler.inverse_transform(y_test)
    y_pred_inverse = flow_scaler.inverse_transform(y_pred_scaled)
    y_pred_inverse = np.maximum(0, y_pred_inverse)  # 确保车数非负

    # 计算评估指标
    rmse_flow = np.sqrt(mean_squared_error(y_test_inverse, y_pred_inverse))
    mae_flow = mean_absolute_error(y_test_inverse, y_pred_inverse)
    r2_flow = r2_score(y_test_inverse, y_pred_inverse)

    print(f"路段 {road_name_original} 预测性能:")
    print(f" 总车数 RMSE: {rmse_flow:.2f}, MAE: {mae_flow:.2f}, R2: {r2_flow:.2f}")

    # 11. 绘制训练损失曲线
    plt.figure(figsize=(10, 5))
    plt.plot(history.history['loss'], label='训练损失')
    plt.plot(history.history['val_loss'], label='验证损失')
    plt.title(f'{road_name_original} GRU模型训练损失')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, f'{road_name_for_filename}_loss_plot.png'))
    plt.close()

    # 12. 绘制预测结果对比图
    num_points_to_plot = min(100, len(y_test_inverse))
    plt.figure(figsize=(12, 6))
    plt.plot(y_test_inverse[:num_points_to_plot], label='真实总车数')
    plt.plot(y_pred_inverse[:num_points_to_plot], label='预测总车数')
    plt.title(f'{road_name_original} 总车数预测对比 (部分)')
    plt.xlabel('时间步')
    plt.ylabel('总车数')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, f'{road_name_for_filename}_prediction_comparison.png'))
    plt.close()
#-----------------------------------------------------------------------------------------------------------
    # 1. 识别历史拥堵点
    print(f"--- 4. 识别 {road_name_original} 交通拥堵高发时段和区域 ---")
    test_start_index_for_df = train_size + sequence_length
    test_times_df = df.iloc[test_start_index_for_df : test_start_index_for_df + len(y_test_inverse)].reset_index(drop=True)

    congestion_flow_threshold_multiplier = 1.2
    historical_avg_flow = df['总车数'].mean()

    congestion_points = test_times_df[
        (test_times_df['总车数'] > historical_avg_flow * congestion_flow_threshold_multiplier)
    ]
    if not congestion_points.empty:
        congestion_points = congestion_points.copy()
        congestion_points['小时'] = congestion_points['测量时间'].dt.hour
        congestion_points['星期几'] = congestion_points['测量时间'].dt.day_name()

    # 2. 预测未来交通状况
    future_predictions_list = []
    current_input_sequence = features_for_model[-sequence_length:].reshape(1, sequence_length, features_for_model.shape[1])
    last_known_time = df['测量时间'].iloc[-1]

    print(f"\n--- 预测未来 {future_prediction_steps * 15 // 60} 小时的交通状况 ---")
    for i in range(future_prediction_steps):
        # 计算下一个预测时间点
        next_time_point = last_known_time + pd.Timedelta(minutes=(i + 1) * 15)
        next_hour = next_time_point.hour
        next_dayofweek = next_time_point.dayofweek

        # 计算时间特征
        next_hour_sin_unscaled = np.sin(2 * math.pi * next_hour / 24)
        next_hour_cos_unscaled = np.cos(2 * math.pi * next_hour / 24)
        next_dayofweek_sin_unscaled = np.sin(2 * math.pi * next_dayofweek / 7)
        next_dayofweek_cos_unscaled = np.cos(2 * math.pi * next_dayofweek / 7)

        # 单步预测
        next_prediction_scaled_flow = model.predict(current_input_sequence, verbose=0)
        predicted_flow_real = flow_scaler.inverse_transform(next_prediction_scaled_flow)[0, 0]
        predicted_flow_real = np.maximum(0, predicted_flow_real)

        future_predictions_list.append({
            'time': next_time_point,
            'flow': predicted_flow_real
        })

        print(f" 预测时间: {next_time_point.strftime('%Y-%m-%d %H:%M')}")
        print(f" 预测总车数: {predicted_flow_real:.2f}")

        # 判断是否拥堵
        is_future_congested_step = (predicted_flow_real > historical_avg_flow * congestion_flow_threshold_multiplier)
        if is_future_congested_step:
            print(f" 预测 {next_time_point.strftime('%H:%M')} 时段将发生拥堵。")
        else:
            print(f" 预测 {next_time_point.strftime('%H:%M')} 时段交通状况良好。")

        # 更新输入序列（用于多步预测）
        new_input_feature_vector_for_next_step = np.array([
            next_prediction_scaled_flow[0,0],
            next_hour_sin_unscaled,
            next_hour_cos_unscaled,
            next_dayofweek_sin_unscaled,
            next_dayofweek_cos_unscaled
        ]).reshape(1, 1, features_for_model.shape[1])
        current_input_sequence = np.concatenate((current_input_sequence[:, 1:, :], new_input_feature_vector_for_next_step), axis=1)

    # 存储拥堵分析结果
    congestion_analysis[road_name_original] = {
        'historical_congested_points': congestion_points,
        'future_predicted_congested_data': future_predictions_list,
        'predicted_flow': future_predictions_list[0]['flow'] if future_predictions_list else None,
        'predicted_time': future_predictions_list[0]['time'] if future_predictions_list else None,
        'is_future_congested': any(p['flow'] > historical_avg_flow * congestion_flow_threshold_multiplier for p in future_predictions_list)
    }

    # 3. 分析历史拥堵时段特征
    if not congestion_points.empty:
        print(f"\n{road_name_original} 历史拥堵高发时段和特征:")
        hourly_congestion = congestion_points['小时'].value_counts().sort_index()
        print(" 拥堵高发小时分布:")
        print(hourly_congestion)

        weekly_congestion = congestion_points['星期几'].value_counts()
        print(" 拥堵高发星期分布:")
        print(weekly_congestion)

        # 绘制拥堵小时分布直方图
        plt.figure(figsize=(10, 5))
        hourly_congestion.plot(kind='bar')
        plt.title(f'{road_name_original} 历史拥堵小时分布')
        plt.xlabel('小时')
        plt.ylabel('拥堵发生次数')
        plt.xticks(rotation=45)
        plt.tight_layout()
        plt.savefig(os.path.join(output_dir, f'{road_name_for_filename}_hourly_congestion.png'))
        plt.close()

    else:
        print(f"\n{road_name_original} 在测试集范围内未识别到符合条件的拥堵点。")
#----------------------------------------------------------------------------------------
# 基于分析结果生成拥堵缓解建议
print("\n--- 5. 提出缓解拥堵的建议 ---")
print("基于对交通流量数据的分析和预测，以下是针对交通拥堵的通用缓解建议：")

for road_name_original, analysis_data in congestion_analysis.items():
    print(f"\n**路段: {road_name_original}**")

    # 分析历史拥堵时段
    if not analysis_data['historical_congested_points'].empty:
        modes = analysis_data['historical_congested_points']['小时'].mode().to_list()
        if modes:
            print(f" 该路段历史拥堵高发时段主要集中在：{modes}点左右。")
        else:
            print(" 该路段历史拥堵时段分布不明确。")
    else:
        print(" 该路段没有足够的历史拥堵数据进行时段分析。")

    # 分析未来预测拥堵情况
    if analysis_data['is_future_congested']:
        print(f" **根据预测，该路段在接下来的 {future_prediction_steps * 15 // 60} 小时内可能出现拥堵。**")
        for pred in analysis_data['future_predicted_congested_data']:
            is_congested = (pred['flow'] > historical_avg_flow * congestion_flow_threshold_multiplier)
            status = "将发生拥堵" if is_congested else "交通状况良好"
            print(f"   - {pred['time'].strftime('%H:%M')} 预测流量: {pred['flow']:.2f} ({status})")
    else:
        print(f" **根据预测，该路段在接下来的 {future_prediction_steps * 15 // 60} 小时内交通状况良好。**")

    # 提出针对性建议
    congested_future_times = [
        pred['time'].strftime('%H:%M') for pred in analysis_data['future_predicted_congested_data']
        if pred['flow'] > historical_avg_flow * congestion_flow_threshold_multiplier
    ]
    if congested_future_times:
        print(f" 针对该路段在未来 {congested_future_times} 时段可能出现的拥堵，建议加强警力部署或采取临时措施。")
    elif not analysis_data['historical_congested_points'].empty and modes:
        print(f" 针对该路段的历史拥堵高发时段 ({modes}点左右)，建议加强警力部署或采取临时措施。")
