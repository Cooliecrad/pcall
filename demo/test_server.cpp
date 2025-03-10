#define __PCALL_SERVER
#include "test.h"

#include <cstdio>
#include "test_table.h"

/**
 * @brief 被调用方/后端/下位机
 */

void move(float dist, uint16_t spd, uint8_t acc)
{
    printf("前进 dist = %f, spd = %d, acc = %d\n", dist, spd, acc);
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

void test_server(const uint8_t *data)
{
    auto server = pcall_init();
    server.parse(data, 120); 
}