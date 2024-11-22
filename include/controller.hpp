#pragma once
#include "main.h"

void control_lifting(pros::Controller &master, pros::Motor &lifting_motor_1, pros::Motor &lifting_motor_2,
                     bool &r1_pressed, bool &r2_pressed);

void control_picker(pros::Controller &master, pros::Motor &picker_motor, bool &l2_pressed);

void control_pneumatic(pros::Controller &master, pros::ADIDigitalOut &pneumatic, bool &lpneumatic_state);