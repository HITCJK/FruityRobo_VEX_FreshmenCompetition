#include "main.h"
#include "parameter.hpp"

PID::PID(double kp, double ki, double kd, double dt, double max_output)
    : kp_(kp), ki_(ki), kd_(kd), dt_(dt), previous_error_(0.0), integral_(0.0), max_output_(max_output)
{
}

double PID::compute(double setpoint, double measured_value)
{
    // 计算误差
    double error = setpoint - measured_value;

    // 计算积分
    integral_ += error * dt_;

    // 计算微分
    double derivative = (error - previous_error_) / dt_;

    // 计算 PID 输出
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;

    // 保存当前误差以供下次计算使用
    previous_error_ = error;

    return (output > max_output_ ? max_output_ : output);
}

void PID::reset()
{
    previous_error_ = 0.0;
    integral_ = 0.0;
}

PID revolve_pid(KP_REVOLVE, KI_REVOLVE, KD_REVOLVE, LOOP_PERIOD, MAXIMUM_MOTOR_SPEED);

PID move_pid(KP_MOVE, KI_MOVE, KD_MOVE, LOOP_PERIOD, MAXIMUM_MOTOR_SPEED);

void revolve(double setpoint)
{
    imu_sensor.set_heading(0);
    revolve_pid.reset();
    pros::lcd::print(5, "Revolve PID");
    while (setpoint - imu_sensor.get_heading() > 5 || setpoint - imu_sensor.get_heading() < -5)
    {
            double speed = revolve_pid.compute(setpoint, imu_sensor.get_heading());
            left_wheels.move_velocity(speed);
            right_wheels.move_velocity(-speed);
    }
}

void move(double setpoint)
{
    move_pid.reset();
}