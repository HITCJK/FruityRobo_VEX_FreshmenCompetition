#pragma once
#include "main.h"

class PID {
public:
    PID(double kp, double ki, double kd, double dt);
    double compute(double setpoint, double measured_value);
    void reset();

private:
    double kp_;            // 比例系数
    double ki_;            // 积分系数
    double kd_;            // 微分系数
    double dt_;            // 采样时间
    double previous_error_; // 上一次误差
    double integral_;      // 积分值
};