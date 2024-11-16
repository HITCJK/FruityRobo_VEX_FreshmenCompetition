#include "main.h"
#include "device.hpp"

// 创建电机组对象（左侧和右侧电机组）
pros::MotorGroup left_wheels({left_front_wheel, left_rear_wheel});
pros::MotorGroup right_wheels({right_front_wheel, right_rear_wheel});

// 定义车辆的当前位置和方向
double current_x = 0.0;
double current_y = 0.0;
double current_heading = 0.0;

pros::Motor hooker_motor_1(5); // 假设端口5
pros::Motor hooker_motor_2(6); // 假设端口6

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

// 其他空函数
void disabled() {}

void competition_initialize() {}

void autonomous() {}

// 手动赛模式
void opcontrol()
{
    const int MAX_VELOCITY = 200; // 最大速度（单位：电机最大速度）

    uint32_t last_time = pros::millis();

    bool r1_pressed = false; // R1 按键状态变量
    bool r2_pressed = false; // R2 按键状态变量

    while (true)
    {
        // 检查 R1 按键状态
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            r1_pressed = !r1_pressed;
            // addition 电机设置反转,履带正走
            hooker_motor_1.set_reversed(true);
            hooker_motor_2.set_reversed(true);
            if (r1_pressed)
            {
                hooker_motor_1.move_velocity(MAX_VELOCITY); // 设置速度为100
                hooker_motor_2.move_velocity(MAX_VELOCITY); // 设置速度为100
            }
            else
            {
                hooker_motor_1.move_velocity(0); // 停止电机
                hooker_motor_2.move_velocity(0); // 停止电机
            }
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
        {
            r2_pressed = !r2_pressed;
            // 履带反走
            hooker_motor_1.set_reversed(false);
            hooker_motor_2.set_reversed(false);
            if (r2_pressed)
            {
                hooker_motor_1.move_velocity(MAX_VELOCITY); // 设置速度为100
                hooker_motor_2.move_velocity(MAX_VELOCITY); // 设置速度为100
            }
            else
            {
                hooker_motor_1.move_velocity(0); // 停止电机
                hooker_motor_2.move_velocity(0); // 停止电机
            }
        }

        // 获取摇杆输入
        int dir = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // 前后方向（左摇杆Y轴）
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // 左右方向（右摇杆X轴）

        dir = -dir; 
        
        // 对于摇杆的微小输入，忽略它们
        if (abs(dir) < 10) dir = 0; // 前后方向
        if (abs(turn) < 10) turn = 0; // 转向方向

        int left_speed = dir - turn;  // 左侧电机速度
        int right_speed = dir + turn; // 右侧电机速度

        if (abs(dir) > 100)
        {
            left_speed = left_speed * 1.2;   // 增加左侧电机加速
            right_speed = right_speed * 1.2; // 增加右侧电机加速
        }
        else if (abs(dir) > 50)
        {
            left_speed = left_speed * 1.1;   // 中等加速
            right_speed = right_speed * 1.1; // 中等加速
        }

        if (abs(turn) > 0)
        {
            left_speed = dir - turn * 1.5;  // 左侧电机转速更高
            right_speed = dir + turn * 1.5; // 右侧电机转速更低
        }

        if (abs(turn) > 50)
        {
            left_speed = dir - turn * 2.0;  // 左侧电机转速更高
            right_speed = dir + turn * 2.0; // 右侧电机转速更低
        }

        left_wheels.move_velocity(std::clamp(left_speed, -MAX_VELOCITY, MAX_VELOCITY));   // 左侧电机组
        right_wheels.move_velocity(std::clamp(right_speed, -MAX_VELOCITY, MAX_VELOCITY)); // 右侧电机组

        uint32_t current_time = pros::millis();
        double delta_time = (current_time - last_time) / 1000.0; // 时间差，单位：秒
        last_time = current_time;

        double rotation = imu_sensor.get_rotation(); // 获取旋转角度
        double accel_x = imu_sensor.get_accel().x;   // 获取X轴加速度
        double accel_y = imu_sensor.get_accel().y;   // 获取Y轴加速度

        current_heading = rotation; // 更新当前方向
        current_x += accel_x * delta_time * delta_time / 2.0; // 更新X坐标
        current_y += accel_y * delta_time * delta_time / 2.0; // 更新Y坐标

        pros::lcd::print(3, "Left Y: %d, Right X: %d", dir, turn);
        pros::lcd::print(4, "X: %f, Y: %f, Heading: %f", current_x, current_y, current_heading);
        pros::lcd::print(5, "Left Speed: %d, Right Speed: %d", left_speed, right_speed);
        
        pros::delay(20);
    }
}