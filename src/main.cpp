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
    pros::lcd::set_text(1, "We are the FruityRobo!");

    // 注册按钮回调函数
    pros::lcd::register_btn1_cb(on_center_button);
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
    bool r1_pressed = false; // R1 按键状态变量
    bool r2_pressed = false; // R2 按键状态变量
    bool pneumatic_state = false;
    bool l2_pressed = false; // L2 按键状态变量

    // imu_sensor.reset(); // 重置IMU传感器
    left_front_wheel.tare_position();  // 重置左前电机编码器
    right_front_wheel.tare_position(); // 重置右前电机编码器
    left_rear_wheel.tare_position();   // 重置左后电机编码器
    right_rear_wheel.tare_position();  // 重置右后电机编码器

    left_front_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);  // 设置编码器单位为度数
    right_front_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES); // 设置编码器单位为度数
    left_rear_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);   // 设置编码器单位为度数
    right_rear_wheel.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);  // 设置编码器单位为度数

    // 重置并校准IMU传感器
    imu_sensor.reset();
    while (true)
    {

        // ------------------------------- 手柄按钮 ------------------------------------
        control_picker(master, picker_motor, l2_pressed);
        control_lifting(master, lifting_motor_1, lifting_motor_2, r1_pressed, r2_pressed);
        control_pneumatic(master, pneumatic, pneumatic_state);
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            revolve(90);
        }
        // ------------------------------- 手柄控制车辆 ------------------------------------
        int power = -master.get_analog(ANALOG_LEFT_Y); // -127 ~ 127
        int turn = -master.get_analog(ANALOG_RIGHT_X);
        int left = power + turn;
        int right = power - turn;

        left_wheels.move(left);
        right_wheels.move(right);

        // ------------------------------- 更新车辆位置 ------------------------------------
        update_position();

        // ------------------------------- 显示信息 ------------------------------------
        // pros::lcd::print(1, "pneumatic: %s", pneumatic_state ? "on" : "off");
        // pros::lcd::print(2, "Lifting: %s", r1_pressed ? "down" : (r2_pressed ? "up" : "stop"));
        // ------------------------------- 等待20ms ------------------------------------
        pros::delay(LOOP_PERIOD);
    }
}