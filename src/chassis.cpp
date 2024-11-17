#include "main.h"
#include "chassis.hpp"

void control_chassis(pros::Controller& master, 
                     pros::MotorGroup& left_wheels, pros::MotorGroup& right_wheels, 
                     int& dir, int& turn,
                     int& left_speed, int& right_speed) 
{
    dir = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // 前后方向（左摇杆Y轴）
    turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // 左右方向（右摇杆X轴）

    dir = -dir; 

    // 对于摇杆的微小输入，忽略它们
    if (abs(dir) < 10) dir = 0; // 前后方向
    if (abs(turn) < 10) turn = 0; // 转向方向

    if (abs(dir) > 100) {
        left_speed = left_speed * 1.2;   // 增加左侧电机加速
        right_speed = right_speed * 1.2; // 增加右侧电机加速
    } else if (abs(dir) > 50) {
        left_speed = left_speed * 1.1;   // 中等加速
        right_speed = right_speed * 1.1; // 中等加速
    }

    if (abs(turn) > 0) {
        left_speed = dir - turn * 1.5;  // 左侧电机转速更高
        right_speed = dir + turn * 1.5; // 右侧电机转速更低
    }

    if (abs(turn) > 50) {
        left_speed = dir - turn * 2.0;  // 左侧电机转速更高
        right_speed = dir + turn * 2.0; // 右侧电机转速更低
    }

    left_wheels.move_velocity(left_speed);
    right_wheels.move_velocity(right_speed);
}
