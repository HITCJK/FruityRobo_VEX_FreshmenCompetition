#include "../include/main.h" // ../ 表示返回上一级目录

// 创建电机组对象（左侧和右侧电机组）
pros::MotorGroup left_wheels({left_front_wheel, left_rear_wheel});    // 左侧电机组
pros::MotorGroup right_wheels({right_front_wheel, right_rear_wheel}); // 右侧电机组

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
    pros::lcd::set_text(1, "We are the Fruit Force Agents!");

    // 注册按钮回调函数
    pros::lcd::register_btn1_cb(on_center_button);

    // 电机组初始化设置
    // 设置右侧电机组反向
    right_wheels.set_reversed(true); // 设置右侧电机组反向
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
    // 自主模式代码
}

// 手动赛模式
void opcontrol()
{
    pros::Controller master(pros::E_CONTROLLER_MASTER); // 创建控制器对象

    // 定义最大速度
    const int MAX_VELOCITY = 200; // 最大速度（单位：电机最大速度）

    while (true)
    {
        // 获取摇杆输入
        int dir = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // 前后方向（左摇杆Y轴）
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // 左右方向（右摇杆X轴）

        // 对于摇杆的微小输入，忽略它们
        // 防止摇杆微小的、不稳定的输入导致机器人有微小的误动作。
        if (abs(dir) < 10)
            dir = 0; // 前后方向
        if (abs(turn) < 10)
            turn = 0; // 转向方向

        // ------------------------ 提高加速性能 ------------------------
        // 增加加速度，尤其是在启动时让机器人更快地加速
        int left_speed = dir - turn;  // 左侧电机速度
        int right_speed = dir + turn; // 右侧电机速度

        // 如果摇杆输入值较大，增加电机的加速比例
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

        // ------------------------ 提高转向性能 ------------------------
        // 在转弯时，通过增大转向差异来提高转向灵活性
        if (abs(turn) > 0)
        {
            left_speed = dir - turn * 1.5;  // 左侧电机转速更高
            right_speed = dir + turn * 1.5; // 右侧电机转速更低
        }

        // ------------------------ 减小转弯半径 ------------------------
        // 通过加大转弯时电机差速来减小转弯半径，使转向更加灵活
        if (abs(turn) > 50)
        {
            left_speed = dir - turn * 2.0;  // 左侧电机转速更高
            right_speed = dir + turn * 2.0; // 右侧电机转速更低
        }

        // 控制电机组的速度：前进 + 转向
        left_wheels.move_velocity(std::clamp(left_speed, -MAX_VELOCITY, MAX_VELOCITY));   // 左侧电机组
        right_wheels.move_velocity(std::clamp(right_speed, -MAX_VELOCITY, MAX_VELOCITY)); // 右侧电机组

        // 显示摇杆状态
        pros::lcd::print(0, "Left Y: %d, Right X: %d", dir, turn);

        // 延时20毫秒
        pros::delay(20);
    }
}
