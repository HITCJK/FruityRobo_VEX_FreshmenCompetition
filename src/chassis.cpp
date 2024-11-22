#include "main.h"

PID::PID(double kp, double ki, double kd, double dt)
    : kp_(kp), ki_(ki), kd_(kd), dt_(dt), previous_error_(0.0), integral_(0.0)
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

    return output;
}

void PID::reset()
{
    previous_error_ = 0.0;
    integral_ = 0.0;
}
