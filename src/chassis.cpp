#include "main.h"
#include <cmath>

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
    if (integral_ > max_output_)
    {
        integral_ = max_output_;
    }
    else if (integral_ < -max_output_)
    {
        integral_ = -max_output_;
    }

    // 计算微分，应用低通滤波器
    double raw_derivative = (error - previous_error_) / dt_;
    constexpr double alpha = 0.5; // 滤波系数，范围在0到1之间，值越小滤波效果越强
    double derivative = alpha * raw_derivative + (1 - alpha) * previous_derivative_;
    previous_derivative_ = derivative;

    // 计算 PID 输出
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;

    // 保存当前误差以供下次计算使用
    previous_error_ = error;

    // 对输出进行限幅
    if (output > max_output_)
    {
        output = max_output_;
    }
    else if (output < -max_output_)
    {
        output = -max_output_;
    }

    return output;
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
    revolve_pid.reset(); // 重置PID控制器
    double current_heading = imu_sensor.get_rotation();
    setpoint = setpoint + imu_sensor.get_rotation();

    const double tolerance = 1;      // 允许的误差范围
    const int timeout = 5000;        // 超时时间，单位为毫秒
    int start_time = pros::millis(); // 记录开始时间

    while (true)
    {
        // 在LCD上打印当前旋转角
        pros::lcd::print(3, "current_heading: %f", imu_sensor.get_rotation());

        // 获取当前旋转角
        current_heading = imu_sensor.get_rotation();

        // 计算旋转角误差
        double error = fmod((setpoint - current_heading), 360.0);
        if (error > 180)
        {
            error -= 360;
        }
        else if (error < -180)
        {
            error += 360;
        }

        // 如果误差在允许范围内，退出循环
        if (fabs(error) <= tolerance)
            break;

        // 计算PID控制器输出的速度
        double speed = revolve_pid.compute(setpoint, current_heading);

        // 设置左轮和右轮速度
        left_wheels.move_velocity(speed);
        right_wheels.move_velocity(-speed);

        // 一些数据
        pros::lcd::print(4, "Time: %d, Setpoint: %f, Current: %f", pros::millis() - start_time, setpoint,
                         current_heading);
        pros::lcd::print(5, "Error: %f, Output: %f", error, speed);

        // 检查是否超时
        if (pros::millis() - start_time > timeout)
            break;

        // 延时10毫秒
        pros::delay(10);
    }

    // 停止电机
    left_wheels.move_velocity(0);
    right_wheels.move_velocity(0);
}

void move(double setpoint)
{
    move_pid.reset();
}