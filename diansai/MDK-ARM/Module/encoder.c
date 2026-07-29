#include "encoder.h"
#define ENCODER_LINE      13      // 编码器线数（一圈的原始脉冲数）
#define REDUCE_RATIO      28.0f   // 减速电机减速比，无减速则设为1
#define SAMPLE_TIME_S     0.01f   // 采样周期，单位秒（1ms = 0.001s）

/************************ 测速相关全局变量 ************************/
volatile float motorL_speed_rpm = 0;    // 最终转速，单位：转/分钟(rpm)
volatile float motorR_speed_rpm = 0;    // 最终转速，单位：转/分钟(rpm)

float get_motorL_speed_rpm(void)
{
    // 静态变量：保存上一次采样的计数器值，仅首次调用初始化为0
    static int16_t last_encoder_cnt = 0;
    
    // 1. 读取当前计数器值，强转为有符号16位（正转计数递增，反转递减）
    int16_t current_cnt = (int16_t)__HAL_TIM_GET_COUNTER(&htim5);
    
    // 2. 计算本次采样周期的脉冲增量（差分法核心，无需清零计数器）
    int16_t delta_cnt = current_cnt - last_encoder_cnt;
    
    // 3. 更新历史计数值，供下一次采样计算使用
    last_encoder_cnt = current_cnt;
    
    // 4. 转速换算（公式与原代码完全一致）
    motorL_speed_rpm = (float)delta_cnt / 4.0f 
                       / ENCODER_LINE 
                        / REDUCE_RATIO 
                        / SAMPLE_TIME_S
                        * 60.0f;
    
    // 5. 返回取反后的转速（与原代码逻辑完全一致）
    return motorL_speed_rpm;
}
float get_motorR_speed_rpm(void)
{
    // 静态变量：保存上一次采样的计数器值，仅首次调用初始化为0
    static int16_t last_encoder_cnt = 0;
    
    // 1. 读取当前计数器值，强转为有符号16位（正转计数递增，反转递减）
    int16_t current_cnt = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);
    
    // 2. 计算本次采样周期的脉冲增量（差分法核心，无需清零计数器）
    int16_t delta_cnt = current_cnt - last_encoder_cnt;
    
    // 3. 更新历史计数值，供下一次采样计算使用
    last_encoder_cnt = current_cnt;
    
    // 4. 转速换算（公式与原代码完全一致）
    motorR_speed_rpm = (float)delta_cnt / 4.0f 
                        / ENCODER_LINE 
                        / REDUCE_RATIO 
                        / SAMPLE_TIME_S
                        * 60.0f;
    
    // 5. 返回取反后的转速（与原代码逻辑完全一致）
    return -motorR_speed_rpm;
}
	







