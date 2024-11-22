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
#define LIFTING_MOTOR_1_PORT 19
#define LIFTING_MOTOR_2_PORT 21

// 气动结构
#define PNEUMATIC_PORT 'h'

// PID参数
#define KP_REVOLVE 6
#define KI_REVOLVE 0
#define KD_REVOLVE 0

#define KP_MOVE 0.001
#define KI_MOVE 0
#define KD_MOVE 0

// loop周期
#define LOOP_PERIOD 20

// 最大电机转速
#define MAXIMUM_MOTOR_SPEED 600