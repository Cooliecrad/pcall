#include "test.h"
#include <cstdio>

/**
 * @brief 最重要的部分：声明本文件为服务器（第四行）和引用共享的头文件（第五行）
 */
#define __PCALL_SERVER // 声明本文件为服务器
#include "table.h" // 引用共享的头文件

/**
 * @brief 被调用方的函数实现
 */

void move(float dist)
{
    printf("前进 dist = %f\n", dist);
}

void arm_x_move(float dist, uint16_t spd, uint8_t acc)
{
    printf("X移动 dist = %f, spd = %d, acc = %d\n", dist, spd, acc);
}

void arm_z_move(float dist, uint16_t spd, uint8_t acc)
{
    printf("Z移动 dist = %f, spd = %d, acc = %d\n", dist, spd, acc);
}

void arm_r_move(float dist, uint16_t spd, uint8_t acc)
{
    printf("R旋转 dist = %f, spd = %d, acc = %d\n", dist, spd, acc);
}

/**
 * @brief 被调用方处理PCall的中间格式（data）
 */

void test_server(const uint8_t *data)
{
    auto server = pcall_init();
    server.parse(data, 120); 
}