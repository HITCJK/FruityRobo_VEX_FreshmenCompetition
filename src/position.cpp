#include "main.h"
#include <cmath>

double x = 0.0;
double y = 0.0;
double theta = 0.0;

//-----------------------------待调参数--------------------------------------
const double WHEEL_BASE = 0.3; // 车辆左右轮之间的距离，单位：米
// 卡尔曼滤波器状态变量
double P[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // 初始协方差矩阵
// 卡尔曼滤波器参数
const double R[3][3] = {{0.1, 0, 0}, {0, 0.1, 0}, {0, 0, 0.1}}; // 过程噪声协方差
const double Q[3][3] = {{0.1, 0, 0}, {0, 0.1, 0}, {0, 0, 0.1}}; // 测量噪声协方差
//--------------------------------------------------------------------------

void update_position()
{
    static double last_left_front_position = 0.0;
    static double last_left_rear_position = 0.0;
    static double last_right_front_position = 0.0;
    static double last_right_rear_position = 0.0;

    double left_front_position = left_front_wheel.get_position();
    double left_rear_position = left_rear_wheel.get_position();
    double right_front_position = right_front_wheel.get_position();
    double right_rear_position = right_rear_wheel.get_position();

    double delta_left_front = left_front_position - last_left_front_position;
    double delta_left_rear = left_rear_position - last_left_rear_position;
    double delta_right_front = right_front_position - last_right_front_position;
    double delta_right_rear = right_rear_position - last_right_rear_position;

    last_left_front_position = left_front_position;
    last_left_rear_position = left_rear_position;
    last_right_front_position = right_front_position;
    last_right_rear_position = right_rear_position;

    double delta_left = (delta_left_front + delta_left_rear) / 2.0;
    double delta_right = (delta_right_front + delta_right_rear) / 2.0;

    double delta_distance = (delta_left + delta_right) / 2.0;
    double delta_theta = (delta_right - delta_left) / WHEEL_BASE;

    // 预测步骤
    double x_pred = x + delta_distance * cos(theta);
    double y_pred = y + delta_distance * sin(theta);
    double theta_pred = theta + delta_theta;

    double P_pred[3][3];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            P_pred[i][j] = P[i][j] + R[i][j];
        }
    }

    // 更新步骤
    double z[3] = {delta_distance, delta_distance, delta_theta};
    double y_k[3] = {z[0] - x_pred, z[1] - y_pred, z[2] - theta_pred};

    double S[3][3];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            S[i][j] = P_pred[i][j] + Q[i][j];
        }
    }

    double K[3][3];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            K[i][j] = P_pred[i][j] / S[i][j];
        }
    }

    x = x_pred + K[0][0] * y_k[0] + K[0][1] * y_k[1] + K[0][2] * y_k[2];
    y = y_pred + K[1][0] * y_k[0] + K[1][1] * y_k[1] + K[1][2] * y_k[2];
    theta = theta_pred + K[2][0] * y_k[0] + K[2][1] * y_k[1] + K[2][2] * y_k[2];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            P[i][j] = (1 - K[i][j]) * P_pred[i][j];
        }
    }

    pros::lcd::print(3, "X: %f, Y: %f, Heading: %f", x, y, theta);
}
