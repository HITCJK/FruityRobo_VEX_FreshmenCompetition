#pragma once
#include "chassis.hpp"
#include "main.h"

class PID
{
  public:
    PID(double kp, double ki, double kd, double dt, double max_output);
    double compute(double setpoint, double measured_value);
    void reset();

  private:
    double kp_;             // 比例系数
    double ki_;             // 积分系数
    double kd_;             // 微分系数
    double dt_;             // 采样时间
    double max_output_;     // 最大输出值
    double previous_error_; // 上一次误差
    double integral_;       // 积分值
    double previous_derivative_; // 上一次微分
};

extern PID revolve_pid;

extern PID move_pid;

void revolve(double setpoint);

void move(double setpoint);
