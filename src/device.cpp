#include "device.hpp"

// 定义电机变量
pros::Motor left_front_wheel(LEFT_FRONT_WHEELS_PORT);
pros::Motor right_front_wheel(RIGHT_FRONT_WHEELS_PORT, true);
pros::Motor left_rear_wheel(LEFT_REAR_WHEELS_PORT);
pros::Motor right_rear_wheel(RIGHT_REAR_WHEELS_PORT, true);