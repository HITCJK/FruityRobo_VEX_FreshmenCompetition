#include "main.h"
#include "chassis.hpp"
#include "device.hpp"
#include "parameter.hpp"
#include <cmath>

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

    // ------------------------------- 初始化设备 ------------------------------------
    left_wheels.set_reversed(true); // 设置左轮反转

    imu_sensor.reset(true); // 重置IMU传感器

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

    clamp(ClampState::UNCLAMP); // 气动结构解夹
}

void disabled()
{
}

void competition_initialize()
{
}

void autonomous()
{
    int magic = 4;
    move(-13.4 - magic, AUTO_SPEED_SLOW - 65);
    clamp(ClampState::CLAMP); // 0-1
    pros::delay(200);
    revolve(180);
    picker(PickerState::INTAKE);
    lifting(LiftingState::UP);
    pros::delay(AUTO_DELAY * 2);

    move(BLOCK - 5.5 - magic, AUTO_SPEED_SLOW); // 1-2 // 后退更多，确保扣到桩
    pros::delay(2 * AUTO_DELAY);
    revolve(-90);
    pros::delay(AUTO_DELAY);

    move(BLOCK - 3, AUTO_SPEED_SLOW - 30); // 2-3
    pros::delay(3 * AUTO_DELAY);
    revolve(-45);
    pros::delay(AUTO_DELAY);     

    move(BLOCK * sqrt(2) - 4, AUTO_SPEED_SLOW - 30); // 3-4
    pros::delay(2 * AUTO_DELAY);
    magic = 7;
    revolve(90 - magic);
    pros::delay(AUTO_DELAY);
    move(BLOCK * sqrt(2) - 8, AUTO_SPEED_SLOW - 30); // 4-5
    pros::delay(3 * AUTO_DELAY);
    lifting(LiftingState::STOP);
    move(-BLOCK * 1 / 2, AUTO_SPEED_SLOW - 30);
    clamp(ClampState::UNCLAMP);
    move(BLOCK * 1 / 2, AUTO_SPEED_SLOW - 30);

    revolve(90);
    pros::delay(AUTO_DELAY);
    magic = 4;
    move(-(BLOCK * sqrt(2) - 6 + magic), AUTO_SPEED_SLOW - 30); // 5-6
    clamp(ClampState::CLAMP);
    lifting(LiftingState::UP);
    pros::delay(100);
    move(magic, AUTO_SPEED_SLOW - 60);
    pros::delay(AUTO_DELAY);

    revolve(-45);
    pros::delay(AUTO_DELAY);
    move(BLOCK - 5.5, AUTO_SPEED_SLOW - 30); // 6-7
    pros::delay(4 * AUTO_DELAY);
}

// 手动赛模式
void opcontrol()
{
    bool r1_pressed = false; // R1 按键状态变量
    bool r2_pressed = false; // R2 按键状态变量
    bool l1_pressed = false; // L1 按键状态变量
    bool l2_pressed = false; // L2 按键状态变量
    double left_flag_position = 0;
    double right_flag_position = 0;
    double heading_flag = 0;

    while (true)
    {
        // ------------------------------- 手柄按钮 ------------------------------------
        control_lifting_and_picking(r1_pressed, r2_pressed);
        control_pneumatic(l2_pressed);
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            autonomous();
        }
        // ------------------------------- 手柄控制车辆 ------------------------------------
        int power = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);
        int left = power + turn;
        int right = power - turn;
        left_wheels.move(left);
        right_wheels.move(right);
        // ------------------------------- 打印信息 ------------------------------------
        pros::lcd::print(3, "heading from flag: %f", imu_sensor.get_rotation() - heading_flag);
        pros::lcd::print(4, "distance from flag: %f",
                         (left_front_wheel.get_position() - left_flag_position + right_front_wheel.get_position() -
                          right_flag_position) /
                             2 / (DST_TO_POS));
        // ------------------------------- 等待 ------------------------------------
        pros::delay(LOOP_PERIOD);
    }
}