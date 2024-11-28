#include "main.h"

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
    // pros::lcd::set_text(1, "We are the FruityRobo!");
    // 注册按钮回调函数
    pros::lcd::register_btn1_cb(on_center_button);

    // ------------------------------- 初始化设备 ------------------------------------
    left_wheels.set_reversed(true); // 设置左轮反转

    imu_sensor.reset(); // 重置IMU传感器

    left_front_wheel.tare_position();  // 重置左前电机编码器
    right_front_wheel.tare_position(); // 重置右前电机编码器
    left_rear_wheel.tare_position();   // 重置左后电机编码器
    right_rear_wheel.tare_position();  // 重置右后电机编码器

    left_front_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    right_front_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    left_rear_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    right_rear_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    // 0: DEGREES: 一圈120
    // 1: ROTATIONS: 一圈0.33
    // 2: COUNTS: 一圈300

    left_front_wheel.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    right_front_wheel.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    left_rear_wheel.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    right_rear_wheel.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

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
    imu_sensor.reset(); // 重置IMU传感器

    bool r1_pressed = false; // R1 按键状态变量
    bool r2_pressed = false; // R2 按键状态变量
    bool l1_pressed = false; // L1 按键状态变量
    bool l2_pressed = false; // L2 按键状态变量

    while (true)
    {
        // ------------------------------- 手柄按钮 ------------------------------------
        control_lifting_and_picking(r1_pressed, r2_pressed);
        control_pneumatic(l2_pressed);
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            move(50);
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
        {
            move(20);
        }
        // ------------------------------- 手柄控制车辆 ------------------------------------
        int power = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);
        int left = power + turn;
        int right = power - turn;
        left_wheels.move(left);
        right_wheels.move(right);
        // ------------------------------- 打印信息 ------------------------------------
        pros::lcd::print(1, "current_heading: %f", imu_sensor.get_rotation());

        // ------------------------------- 等待 ------------------------------------
        pros::delay(LOOP_PERIOD);
    }
}