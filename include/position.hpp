#pragma once
#include "pros/imu.hpp"

// 定义全局变量
extern double current_x;
extern double current_y;
extern double current_heading;

// 函数声明
void update_position(pros::Imu &imu_sensor, double delta_time);
