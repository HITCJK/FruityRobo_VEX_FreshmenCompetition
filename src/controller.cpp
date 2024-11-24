#include "main.h"

const int MAX_VELOCITY = 200; // 最大速度（单位：电机最大速度）

// R2 按键控制抬升结构, R1 按键使履带反走
void control_lifting_and_picking(bool &r1_pressed, bool &r2_pressed)
{
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
    {
        r2_pressed = !r2_pressed;

        if(r2_pressed)
        {
            picker_motor.move_velocity(MAX_VELOCITY);
            lifting_motor_1.move_velocity(MAX_VELOCITY);
            lifting_motor_2.move_velocity(MAX_VELOCITY);
        }
        else
        {
            picker_motor.move_velocity(0); // 停止电机
            lifting_motor_1.move_velocity(0); // 停止电机
            lifting_motor_2.move_velocity(0); // 停止电机
        }
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        r1_pressed = !r1_pressed;

        if(r1_pressed)
        {
            lifting_motor_1.move_velocity(-MAX_VELOCITY);
            lifting_motor_2.move_velocity(-MAX_VELOCITY);
        }
        else
        {
            lifting_motor_1.move_velocity(0); // 停止电机
            lifting_motor_2.move_velocity(0); // 停止电机
        }
    }
}

// L2 按键控制气动结构
void control_pneumatic(bool &l2_pressed)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
        l2_pressed = !l2_pressed;

        if (l2_pressed)
        {
            pneumatic.set_value(true);
        }
        else
        {
            pneumatic.set_value(false);
        }
    }
}
