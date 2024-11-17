#include "controller.hpp"
#include "main.h"

const int MAX_VELOCITY = 200; // 最大速度（单位：电机最大速度）

void control_lifting(pros::Controller &master, pros::Motor &lifting_motor_1, pros::Motor &lifting_motor_2,
                     bool &r1_pressed, bool &r2_pressed)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        r1_pressed = !r1_pressed;
        // 切换电机方向
        lifting_motor_1.set_reversed(!lifting_motor_1.is_reversed());
        lifting_motor_2.set_reversed(!lifting_motor_2.is_reversed());

        if (r1_pressed)
        {
            lifting_motor_1.move_velocity(MAX_VELOCITY); // 设置速度为100
            lifting_motor_2.move_velocity(MAX_VELOCITY); // 设置速度为100
        }
        else
        {
            lifting_motor_1.move_velocity(0); // 停止电机
            lifting_motor_2.move_velocity(0); // 停止电机
        }
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
    {
        r2_pressed = !r2_pressed;
        // 扣环方向
        lifting_motor_1.set_reversed(true);
        lifting_motor_2.set_reversed(true);
        if (r2_pressed)
        {
            lifting_motor_1.move_velocity(MAX_VELOCITY); // 设置速度为100
            lifting_motor_2.move_velocity(MAX_VELOCITY); // 设置速度为100
        }
        else
        {
            lifting_motor_1.move_velocity(0); // 停止电机
            lifting_motor_2.move_velocity(0); // 停止电机
        }
    }
}

void control_picker(pros::Controller &master, pros::Motor &picker_motor, bool &l1_pressed, bool &l2_pressed)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
    {
        l1_pressed = !l1_pressed;
        if (l1_pressed)
        {
            picker_motor.move_velocity(MAX_VELOCITY);
        }
        else
        {
            picker_motor.move_velocity(0);
        }
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
        l2_pressed = !l2_pressed;
        if (l2_pressed)
        {
            picker_motor.move_velocity(-MAX_VELOCITY);
        }
        else
        {
            picker_motor.move_velocity(0);
        }
    }
}