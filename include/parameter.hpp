#pragma once

#define LEFT_FRONT_WHEELS_PORT 2
#define RIGHT_FRONT_WHEELS_PORT 1
#define LEFT_REAR_WHEELS_PORT 12
#define RIGHT_REAR_WHEELS_PORT 11

// 惯性传感器
#define IMU_PORT 13

// 吃环结构
#define PICKER_MOTOR_PORT 4

// 抬升、扣环结构
#define LIFTING_MOTOR_1_PORT 20
#define LIFTING_MOTOR_2_PORT 21

// 气动结构
#define PNEUMATIC_PORT 'h'

// PID参数
#define KP_REVOLVE 1.4
#define KI_REVOLVE 0
#define KD_REVOLVE 0
#define STABLE_TIME_THRESHOLD 50

#define KP_MOVE 0.5
#define KI_MOVE 0
#define KD_MOVE (-5)

// loop周期
#define LOOP_PERIOD 10

// 车轮电机：蓝色(600)
// 其他电机：绿色(200)
#define MAX_VELOCITY 200
#define MAXIMUM_MOTOR_SPEED 600

// 车子的物理参数
#define WHEEL_DIAMETER 4.0                                                      // 车轮直径
#define GEAR_RATIO (36.0 / 84.0)                                                // 齿轮比
#define ENCODER_TICKS_PER_REV 120                                               // 每转编码器的position变化值
#define DST_TO_POS ENCODER_TICKS_PER_REV / (WHEEL_DIAMETER * M_PI) / GEAR_RATIO // 距离到position的转换系数
#define ROBOT_WIDTH 10.0                                                        // 车宽
#define ROBOT_LENGTH 10.0                                                       // 车长

// 场地参数
#define BLOCK 24.0


#define AUTO_SPEED 200
#define AUTO_SPEED_SLOW 100
#define AUTO_SPEED_FAST 300