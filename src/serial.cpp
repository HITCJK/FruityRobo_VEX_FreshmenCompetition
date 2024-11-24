#include "pros/serial.h"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.h"


void read_serial_data()
{
    uint8_t port = 5;        // 使用的V5端口号
    int32_t baudrate = 9600; // 波特率

    // 启用串口
    pros::c::serial_enable(port);
    pros::c::serial_set_baudrate(port, baudrate);

    while (true)
    {
        // 检查是否有数据可读
        int32_t available = pros::c::serial_get_read_avail(port);
        if (available > 0)
        {
            uint8_t buffer[available];
            pros::c::serial_read(port, buffer, available);

            // 打印读取到的数据
            for (int i = 0; i < available; i++)
            {
                printf("%c", buffer[i]);
            }
        }
        else
        {
            pros::lcd::print(0, "No data available");
        }

        // 延迟以避免占用过多CPU时间
        pros::delay(20);
    }
}
