#pragma once
#include "main.h"

// 要和使用的函数放在一起
enum class PickerState
{
    INTAKE,
    STOP,
    REVERSE
};
enum class LiftingState
{
    UP,
    DOWN,
    STOP
};
enum class ClampState
{
    CLAMP,
    UNCLAMP
};
extern void picker(PickerState state);
extern void picker(PickerState state, int velocity);
extern void lifting(LiftingState state);
extern void clamp(ClampState state);

// 车轮
extern pros::Motor left_front_wheel;
extern pros::Motor right_front_wheel;
extern pros::Motor left_rear_wheel;
extern pros::Motor right_rear_wheel;
extern pros::MotorGroup left_wheels;
extern pros::MotorGroup right_wheels;
extern pros::MotorGroup all_wheels;

// 惯性传感器
extern pros::Imu imu_sensor;

// 手柄
extern pros::Controller master;

// 抬升、扣环结构
extern pros::Motor lifting_motor_1;
extern pros::Motor lifting_motor_2;

// 吃环结构
extern pros::Motor picker_motor;

// 气动结构
extern pros::ADIDigitalOut pneumatic;