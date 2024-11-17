
#include "main.h"


template <typename T> const T &clamp(const T &v, const T &lo, const T &hi)
{
    return (v < lo) ? lo : (v > hi) ? hi : v;
}

// 初始化全局变量
double current_x = 0.0;
double current_y = 0.0;
double current_heading = 0.0;

void update_position(pros::Imu &imu_sensor, double delta_time)
{
    double rotation = imu_sensor.get_rotation();
    double accel_x = imu_sensor.get_accel().x;
    double accel_y = imu_sensor.get_accel().y;

    current_heading = rotation;
    current_x += accel_x * delta_time * delta_time / 2.0;
    current_y += accel_y * delta_time * delta_time / 2.0;
}