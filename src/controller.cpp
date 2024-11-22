#include "main.h"

const int MAX_VELOCITY = 200; // 最大速度（单位：电机最大速度）

// R1、R2 按键控制抬升、扣环结构
void control_lifting(pros::Controller &master, pros::Motor &lifting_motor_1, pros::Motor &lifting_motor_2,
                     bool &r1_pressed, bool &r2_pressed)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        r1_pressed = !r1_pressed;

        if (r1_pressed)
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
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
    {
        r2_pressed = !r2_pressed;
        // 扣环方向

        if (r2_pressed)
        {
            lifting_motor_1.move_velocity(MAX_VELOCITY);
            lifting_motor_2.move_velocity(MAX_VELOCITY);
        }
        else
        {
            lifting_motor_1.move_velocity(0); // 停止电机
            lifting_motor_2.move_velocity(0); // 停止电机
        }
    }
}

// L2 按键控制吃环结构
void control_picker(pros::Controller &master, pros::Motor &picker_motor, bool &l2_pressed)
{
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

// L1 按键控制气动结构
void control_pneumatic(pros::Controller &master, pros::ADIDigitalOut &pneumatic, bool &pneumatic_state)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
    {
        pneumatic_state = !pneumatic_state;
        pneumatic.set_value(pneumatic_state);
    }
}
