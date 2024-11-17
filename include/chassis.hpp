#pragma once
#include "main.h"

void control_chassis(pros::Controller &master, pros::MotorGroup &left_wheels, pros::MotorGroup &right_wheels, int &dir,
                     int &turn, int &left_speed, int &right_speed);