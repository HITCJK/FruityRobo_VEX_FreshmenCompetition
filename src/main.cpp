#include "main.h"

// 电机组初始化
pros::MotorGroup left_mg({1, 2});
pros::MotorGroup right_mg({3, 4});

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
    pros::lcd::initialize();
    pros::lcd::set_text(1, "We are the Fruit Force Agents!");

    pros::lcd::register_btn1_cb(on_center_button); // 注册按钮回调
}

// 其他空函数
void disabled()
{
}
void competition_initialize()
{
}
void autonomous()
{
}

// 手动赛模式
void opcontrol()
{
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    while (true)
    {
        // 获取摇杆输入
        int dir = master.get_analog(ANALOG_LEFT_Y);   // 前后
        int turn = master.get_analog(ANALOG_RIGHT_X); // 左右

        // 对于摇杆的微小输入，忽略它们
        // 比如，摇杆的数值小于某个阈值时，认为是没有输入，避免细微不稳定的动作。
        if (abs(dir) < 10)
            dir = 0; // 前后方向
        if (abs(turn) < 10)
            turn = 0; // 转向

        // 控制电机的速度：前进 + 转向
        left_mg.move(dir - turn);
        right_mg.move(dir + turn);

        // 显示摇杆状态
        pros::lcd::print(0, "Left Y: %d, Right X: %d", dir, turn);

        // 延时20毫秒
        pros::delay(20);
    }
}
