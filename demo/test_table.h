#include "pcall.h"

/**
 * @brief 要用到的函数
 */

void move(float dist, uint16_t spd, uint8_t acc);
void arm_x_move(float dist, uint16_t spd, uint8_t acc);
void arm_z_move(float dist, uint16_t spd, uint8_t acc);
void arm_r_move(float dist, uint16_t spd, uint8_t acc);

pcall_begin()
    pcall_item(move, "移动", float, "dist", uint16_t, "spd", uint16_t, "acc")
    pcall_item(arm_x_move, "x移动", float, "dist", uint16_t, "spd", uint16_t, "acc")
    pcall_item(arm_z_move, "y移动", float, "dist", uint16_t, "spd", uint8_t, "acc")
    pcall_item(arm_r_move, "r移动", float, "dist", uint16_t, "spd", uint8_t, "acc")
pcall_end()

pcall_table_being()
    pcalll_table_item('m', move),
    pcalll_table_item('x', arm_x_move),
    pcalll_table_item('z', arm_z_move),
    pcalll_table_item('r', arm_r_move),
pcall_table_end()