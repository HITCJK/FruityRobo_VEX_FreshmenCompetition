#include "main.h"

// 车轮
pros::Motor left_front_wheel(LEFT_FRONT_WHEELS_PORT);
pros::Motor right_front_wheel(RIGHT_FRONT_WHEELS_PORT);
pros::Motor left_rear_wheel(LEFT_REAR_WHEELS_PORT);
pros::Motor right_rear_wheel(RIGHT_REAR_WHEELS_PORT);
pros::MotorGroup left_wheels({left_front_wheel, left_rear_wheel});
pros::MotorGroup right_wheels({right_front_wheel, right_rear_wheel});
pros::MotorGroup all_wheels({left_front_wheel, right_front_wheel, left_rear_wheel, right_rear_wheel});

// 惯性传感器
pros::Imu imu_sensor(IMU_PORT);

// 手柄
pros::Controller master(pros::E_CONTROLLER_MASTER);

// 吃环结构
pros::Motor picker_motor(PICKER_MOTOR_PORT, true);

// 抬升、扣环结构
pros::Motor lifting_motor_1(LIFTING_MOTOR_1_PORT);
pros::Motor lifting_motor_2(LIFTING_MOTOR_2_PORT, true);

// 气动结构
pros::ADIDigitalOut pneumatic(PNEUMATIC_PORT, false);

void picker(PickerState state)
{
    switch (state)
    {
    case PickerState::INTAKE:
        picker_motor.move_velocity(MAX_VELOCITY);
        break;
    case PickerState::STOP:
        picker_motor.move_velocity(0);
        break;
    case PickerState::REVERSE:
        picker_motor.move_velocity(-MAX_VELOCITY);
        break;
    }
}

void picker(PickerState state, int velocity)
{
    switch (state)
    {
    case PickerState::INTAKE:
        picker_motor.move_velocity(velocity);
        break;
    case PickerState::STOP:
        picker_motor.move_velocity(0);
        break;
    case PickerState::REVERSE:
        picker_motor.move_velocity(-velocity);
        break;
    }
}

void lifting(LiftingState state)
{
    switch (state)
    {
    case LiftingState::UP:
        lifting_motor_1.move_velocity(MAX_VELOCITY);
        lifting_motor_2.move_velocity(MAX_VELOCITY);
        break;
    case LiftingState::DOWN:
        lifting_motor_1.move_velocity(-MAX_VELOCITY);
        lifting_motor_2.move_velocity(-MAX_VELOCITY);
        break;
    case LiftingState::STOP:
        lifting_motor_1.move_velocity(0);
        lifting_motor_2.move_velocity(0);
        break;
    }
}

void clamp(ClampState state)
{
    switch (state)
    {
    case ClampState::CLAMP:
        pneumatic.set_value(false);
        break;
    case ClampState::UNCLAMP:
        pneumatic.set_value(true);
        break;
    }
}