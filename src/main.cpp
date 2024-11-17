#include "main.h"
#include "chassis.hpp"
#include "controller.hpp"
#include "device.hpp"
#include "position.hpp"
#include "pros/motors.hpp"


#include <algorithm>

// 定义车辆的当前位置和方向
double current_x = 0.0;
double current_y = 0.0;
double current_heading = 0.0;

// LCD按钮回调函数
void on_center_button()
{
    static bool pressed = false;
    pressed = !pressed;
    if (pressed)
    {
        pros::lcd::set_text(2, "I was pressed!");
    }
    else
    {
        pros::lcd::clear_line(2);
    }
}

// 初始化函数
void initialize()
{
    // 初始化LCD屏幕并显示队名
    pros::lcd::initialize();
    pros::lcd::set_text(1, "We are the FruityRobo!");

    // 注册按钮回调函数
    pros::lcd::register_btn1_cb(on_center_button);

    // 电机组初始化设置
    right_wheels.set_reversed(true); // 设置右侧电机组反向
}

void disabled()
{
}

void competition_initialize()
{
}

void autonomous()
{
    // 初始化
    const double MAX_VELOCITY = 200.0; // 最大速度
    uint32_t last_time = pros::millis();
    double current_x = 0.0, current_y = 0.0, current_heading = 0.0;

    // 预定路径和任务
    std::vector<std::pair<double, double>> path = {
        {1.0, 0.0}, // 向前移动1米
        {1.0, 1.0}, // 向右移动1米
        {0.0, 1.0}  // 向后移动1米
    };

    for (const auto &target : path)
    {
        double target_x = target.first;
        double target_y = target.second;

        while (true)
        {
            // 获取传感器数据
            uint32_t current_time = pros::millis();
            double delta_time = (current_time - last_time) / 1000.0;
            last_time = current_time;

            // 更新车辆位置
            update_position(imu_sensor, delta_time);

            // 计算误差
            double error_x = target_x - current_x;
            double error_y = target_y - current_y;

            // 简单的比例控制器
            double kP = 1.0;
            double left_speed = kP * error_x - kP * error_y;
            double right_speed = kP * error_x + kP * error_y;

            left_wheels.move_velocity(std::clamp(left_speed, -MAX_VELOCITY, MAX_VELOCITY));
            right_wheels.move_velocity(std::clamp(right_speed, -MAX_VELOCITY, MAX_VELOCITY));

            // 判断是否到达目标点
            if (std::abs(error_x) < 0.1 && std::abs(error_y) < 0.1)
            {
                break;
            }

            pros::delay(20);
        }
    }

    // 停止电机
    left_wheels.move_velocity(0);
    right_wheels.move_velocity(0);
}

// 手动赛模式
void opcontrol()
{

    uint32_t last_time = pros::millis();

    bool r1_pressed = false; // R1 按键状态变量
    bool r2_pressed = false; // R2 按键状态变量
    bool l1_pressed = false; // L1 按键状态变量
    bool l2_pressed = false; // L2 按键状态变量

    // 定义变量，以便把底盘运动代码移动到chasiss.cpp中
    int dir = 0;
    int turn = 0;
    int left_speed = 0;
    int right_speed = 0;

    while (true)
    {
        // ------------------------------- 手柄按钮 ------------------------------------
        control_chassis(master, left_wheels, right_wheels, dir, turn, left_speed, right_speed);
        control_lifting(master, lifting_motor_1, lifting_motor_2, r1_pressed, r2_pressed);

        // ------------------------------- 手柄控制车辆 ------------------------------------
        control_chassis(master, left_wheels, right_wheels, dir, turn, left_speed, right_speed);

        // ------------------------------- 更新车辆位置 ------------------------------------
        uint32_t current_time = pros::millis();
        double delta_time = (current_time - last_time) / 1000.0; // 时间差，单位：秒
        last_time = current_time;

        update_position(imu_sensor, delta_time);

        // ------------------------------- 显示信息 ------------------------------------
        pros::lcd::print(3, "Left Y: %d, Right X: %d", dir, turn);
        pros::lcd::print(4, "X: %f, Y: %f, Heading: %f", current_x, current_y, current_heading);
        pros::lcd::print(5, "Left Speed: %d, Right Speed: %d", left_speed, right_speed);

        // ------------------------------- 等待20ms ------------------------------------
        pros::delay(20);
    }
}