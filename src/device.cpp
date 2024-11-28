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
