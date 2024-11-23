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

    // 计算积分并进行限幅
    integral_ += error * dt_;
    if (integral_ > max_output_)
    {
        integral_ = max_output_;
    }
    else if (integral_ < -max_output_)
    {
        integral_ = -max_output_;
    }

    // 计算微分
    double derivative = (error - previous_error_) / dt_;

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
    imu_sensor.tare_rotation();   // 重置IMU传感器的偏航角
    revolve_pid.reset();          // 重置PID控制器
    
    const double tolerance = 5.0; // 允许的误差范围
    const int timeout = 5000;     // 超时时间，单位为毫秒
    int start_time = pros::millis(); // 记录开始时间
    
    while (true)
    {
        // 在LCD上打印当前旋转角
        pros::lcd::print(5, "current_heading: %f", imu_sensor.get_rotation());
        
        // 获取当前旋转角
        double current_heading = imu_sensor.get_rotation();
        
        // 计算旋转角误差
        double error = setpoint - current_heading;
    
        // 如果误差在允许范围内，退出循环
        if (fabs(error) <= tolerance)
            break;
    
        // 计算PID控制器输出的速度
        double speed = revolve_pid.compute(setpoint, current_heading);
        
        // 设置左轮和右轮速度
        left_wheels.move_velocity(speed);
        right_wheels.move_velocity(-speed);
    
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