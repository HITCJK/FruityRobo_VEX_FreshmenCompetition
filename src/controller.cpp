#include "main.h"

// R2 按键控制抬升结构, R1 按键使履带反走
void control_lifting_and_picking(bool &r1_pressed, bool &r2_pressed)
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
    {
        r2_pressed = !r2_pressed;

        if (r2_pressed)
        {
            picker(PickerState::INTAKE);          // 吃环电机正转
            lifting(LiftingState::UP);        // 抬升电机正转
        }
        else
        {
            picker(PickerState::STOP);         // 吃环电机停止
            lifting(LiftingState::STOP);      // 抬升电机停止
        }
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        r1_pressed = !r1_pressed;

        if (r1_pressed)
        {
            lifting(LiftingState::DOWN);
        }
        else
        {
            lifting(LiftingState::STOP);
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
            clamp(ClampState::CLAMP);
        }
        else
        {
            clamp(ClampState::UNCLAMP);
        }
    }
}
