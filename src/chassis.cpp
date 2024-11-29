#include "main.h"


PID::PID(double kp, double ki, double kd, double dt, double max_output)
    : kp_(kp), ki_(ki), kd_(kd), dt_(dt), previous_error_(0.0), integral_(0.0), max_output_(max_output)
{
}

double PID::compute(double setpoint, double measured_value)
{
    // 计算误差
    double error = setpoint - measured_value;
    return PID::compute(error);
}

double PID::compute(double error)
{
    // 计算积分
    integral_ += error * dt_;

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

//--------------------------------- PID控制器 ------------------------------------
PID revolve_pid(KP_REVOLVE, KI_REVOLVE, KD_REVOLVE, LOOP_PERIOD, MAXIMUM_MOTOR_SPEED);
PID move_pid(KP_MOVE, KI_MOVE, KD_MOVE, LOOP_PERIOD, MAXIMUM_MOTOR_SPEED);

void revolve(double setpoint)
{
    revolve_pid.reset(); // 重置PID控制器
    double current_heading = imu_sensor.get_rotation();
    setpoint = setpoint + imu_sensor.get_rotation();

    const double tolerance = 0.5;    // 允许的误差范围
    const int timeout = 5000;        // 超时时间，单位为毫秒
    int start_time = pros::millis(); // 记录开始时间
    int stable_time = 0;
    const int stable_time_threshold = STABLE_TIME_THRESHOLD;
    const int initial_rotation = imu_sensor.get_rotation();

    while (true)
    {
        // 在LCD上打印当前旋转角
        pros::lcd::print(0, "Heading changed last rev: %2f", imu_sensor.get_rotation() - initial_rotation);

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

        // 如果误差在允许范围内，稳定时间加1
        if (fabs(error) <= tolerance)
        {
            stable_time++;
        }
        else
        {
            stable_time = 0;
        }
        if (stable_time >= stable_time_threshold)
        {
            break;
        }

        // 计算PID控制器输出的速度
        double speed = revolve_pid.compute(error);

        // 设置左轮和右轮速度
        left_wheels.move_velocity(speed);
        right_wheels.move_velocity(-speed);

        // 检查是否超时
        if (pros::millis() - start_time > timeout)
            break;

        // 延时10毫秒
        pros::delay(LOOP_PERIOD);
    }

    // 停止电机
    all_wheels.brake();
}

void move(double target_distance,int velocity)
{
    const double target_position = target_distance * DST_TO_POS;
    const double tolerance = 5;
    const double initial_left_position = left_front_wheel.get_position();
    const double initial_right_position = right_front_wheel.get_position();

    all_wheels.move_relative(target_position, velocity);
    while (fabs(left_front_wheel.get_position() - initial_left_position - target_position) > tolerance &&
           fabs(right_front_wheel.get_position() - initial_right_position - target_position) > tolerance)
    {
        pros::delay(5);
    }
    
}

// void move_(double target_distance) // 单位：英寸
// {
//     const double initial_left_position = left_front_wheel.get_position();
//     const double initial_right_position = right_front_wheel.get_position();
//     const double target_position = target_distance * DST_TO_POS;
//     double current_position = 0; // 当前距离
//     const double tolerance = 5;

//     const int timeout = target_distance * 100; // 超时时间，单位为毫秒，用distance计算
//     const int start_time = pros::millis();     // 记录开始时间

//     while (fabs(current_position - target_position) > tolerance)
//     {
//         // 设置左右轮速度
//         double speed = move_pid.compute(target_position, current_position);
//         all_wheels.move_velocity(speed);
//         // if(pros::millis() - start_time > 10)
//         // {
//         //     pros::delay(5);
//         // }
        

//         // 更新当前距离
//         current_position = (left_front_wheel.get_position() - initial_left_position + right_front_wheel.get_position() -
//                             initial_right_position) /
//                            2;

//         // 在LCD上打印
//         pros::lcd::print(4, "current_distance: %f", current_position / DST_TO_POS);

//         // 检查是否超时
//         if (pros::millis() - start_time > timeout)
//         {
//             break;
//             pros::lcd::print(2, "timeout");
//         }

//         // 延时10毫秒
//         pros::delay(LOOP_PERIOD);
//     }
//     // 停止电机
//     all_wheels.brake();
// }