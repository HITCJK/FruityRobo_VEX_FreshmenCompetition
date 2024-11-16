# PROS介绍
- 官网https://pros.cs.purdue.edu/v5/api/cpp/index.html

# 基本API

## VEX Inertial Sensor C++ API (惯性传感器)
### 创建&初始化
> pros::Imu imu_sensor(IMU_PORT);
> imu_sensor.reset();

### 常用函数
- get_rotation 累计旋转角
- get_heading 相对于初始位置的航向角（0~360）
- get_yaw 偏航角（-180~180）
- set系列

## LLEMU (Legacy LCD Emulator) C++ API （主控屏幕）
- 可以用于在主控上输出调试信息，如车的坐标等

## Motors C++ API （电机，非常重要）
### 创建&初始化
> pros::Motor motor (1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
> motor.set_brake_mode() （决定电机刹车行为（滑行/刹停））
> motor.tare_position() （将当前电机状态置为编码器的0点，对定位非常重要）
### 常用函数
- move_velocity 注意输入大小与电机匹配，通过电机内置PID保持
- move_voltage 直接给定输入电压
- get_position 获得电机内置编码器的位置信息，即转了多少个单位（一般是角度）


## Controller C++ API （手柄,在Miscellaneous C++ API中）
### 创建&初始化
> pros::Controller master (E_CONTROLLER_MASTER);
### 常用函数
- get_analog() 获取摇杆读数（注意X,Y方向是分开读的）
- get_digital() 获取某一按键是否按下
- get_digital_new_press() 检测上升沿（即按下的瞬间）
- print() 可以用于在手柄上输出调试信息，如车的坐标等

## ADI (TriPort) C++ API （控制三线接口，用于控制气缸等）
### 创建&初始化
> pros::ADIDigitalOut pneumatic (DIGITAL_SENSOR_PORT, false); （气缸直接用数字信号控制）
### 常用函数
- set_value()

## RTOS Facilities C++ API （任务管理）
- https://pros.cs.purdue.edu/v5/api/cpp/rtos.html
- https://pros.cs.purdue.edu/v5/tutorials/topical/multitasking.html

## 其他常用函数
- pros::delay() 在设置完电机参数后，程序不会暂停，需要此函数实现延时

# 程序构成

parameter.hpp       （基本参数，包括各种端口）
device.hpp          （各种设备的实例化）
chassis.hpp         （底盘的运动控制等）
(position.hpp)      （定位）
(controller.hpp)    （按键检测与对应需要执行的函数）

记得放在main.h的对应位置里