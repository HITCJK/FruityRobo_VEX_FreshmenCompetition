#include "main.h"
#include <cmath>
#include <limits>

// double x = 0.0;
// double y = 0.0;
// double theta = 0.0;
// double theta_degree = 0.0;

// // 车辆参数
// const double INCH_TO_METER = 0.0254;                                 // 1 英寸等于 0.0254 米
// const double WHEEL_RADIUS = 4.0 * INCH_TO_METER;                     // 轮子的半径，单位：米
// const double radianToDegree = 57.2957795;                            // 弧度到度数的转换常量
// const double MIN_THRESHOLD = std::numeric_limits<double>::epsilon(); // 最小阈值

// //--------------------待调参数--------------------
// // 卡尔曼滤波器状态变量
// double P[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // 初始协方差矩阵

// // 卡尔曼滤波器参数
// const double R[3][3] = {{0.1, 0, 0}, {0, 0.1, 0}, {0, 0, 0.1}}; // 过程噪声协方差
// const double Q[3][3] = {{0.1, 0, 0}, {0, 0.1, 0}, {0, 0, 0.1}}; // 测量噪声协方差
// //------------------------------------------------

// void update_position()
// {
//     static double last_left_front_position = 0.0;
//     static double last_left_rear_position = 0.0;
//     static double last_right_front_position = 0.0;
//     static double last_right_rear_position = 0.0;

//     double left_front_position = left_front_wheel.get_position();
//     double left_rear_position = left_rear_wheel.get_position();
//     double right_front_position = right_front_wheel.get_position();
//     double right_rear_position = right_rear_wheel.get_position();

//     double delta_left_front = left_front_position - last_left_front_position;
//     double delta_left_rear = left_rear_position - last_left_rear_position;
//     double delta_right_front = right_front_position - last_right_front_position;
//     double delta_right_rear = right_rear_position - last_right_rear_position;

//     last_left_front_position = left_front_position;
//     last_left_rear_position = left_rear_position;
//     last_right_front_position = right_front_position;
//     last_right_rear_position = right_rear_position;

//     // 将度数转换为弧度
//     double delta_left_front_rad = delta_left_front * M_PI / 180.0;
//     double delta_left_rear_rad = delta_left_rear * M_PI / 180.0;
//     double delta_right_front_rad = delta_right_front * M_PI / 180.0;
//     double delta_right_rear_rad = delta_right_rear * M_PI / 180.0;

//     // 计算线位移
//     double delta_left_front_dist = delta_left_front_rad * WHEEL_RADIUS;
//     double delta_left_rear_dist = delta_left_rear_rad * WHEEL_RADIUS;
//     double delta_right_front_dist = delta_right_front_rad * WHEEL_RADIUS;
//     double delta_right_rear_dist = delta_right_rear_rad * WHEEL_RADIUS;

//     double delta_left = (delta_left_front_dist + delta_left_rear_dist) / 2.0;
//     double delta_right = (delta_right_front_dist + delta_right_rear_dist) / 2.0;
//     double delta_distance = (delta_left + delta_right) / 2.0;

//     // 等待IMU传感器校准完成
//         while (imu_sensor.is_calibrating()) {
//         pros::lcd::print(0, "IMU calibrating ...");
//         pros::delay(20);
//         }

//         pros::lcd::print(0, "IMU calibrated!");
    
//     // 使用惯性传感器获取角度
//     double imu_angle = imu_sensor.get_rotation() * M_PI / 180.0; // 将度数转换为弧度

//     // 应用下限阈值
//     if (std::abs(delta_distance) < MIN_THRESHOLD)
//     {
//         delta_distance = 0.0;
//     }

//     // 预测步骤
//     double x_pred = x + delta_distance * cos(imu_angle);
//     double y_pred = y + delta_distance * sin(imu_angle);

//     // 检查是否有非法操作
//     if (std::isnan(x_pred) || std::isnan(y_pred) || std::isinf(x_pred) || std::isinf(y_pred))
//     {
//         pros::lcd::print(6, "Error: Invalid predicted values");
//         pros::lcd::print(7, "x_p: %.3f, y_p: %.3f, angle: %.3f", x_pred, y_pred, imu_angle);
        
//         return;
//     }

//     // 更新位置和方向
//     x = x_pred;
//     y = y_pred;
//     theta = imu_angle;


//     // 打印变量到LCD屏幕
//     pros::lcd::print(2, "X: %.1f, Y: %.1f, Heading: %.1f°", x, y, fmod(theta, 2 * M_PI) * radianToDegree);
//     pros::lcd::print(3, "");
//     pros::lcd::print(4, "");
//     pros::lcd::print(5, "");
//     pros::lcd::print(6, "");
//     pros::lcd::print(7, "");
// }
