#pragma once
#include "main.h"

// 声明电机变量
extern pros::Motor left_front_wheel;
extern pros::Motor right_front_wheel;
extern pros::Motor left_rear_wheel;
extern pros::Motor right_rear_wheel;


extern pros::Imu imu_sensor;

// pros::Controller master(pros::E_CONTROLLER_MASTER); // 创建控制器对象
extern pros::Controller master;

