#include "pcall.h"

/**
 * @brief 示例程序：如何编写函数调用声明 
 */

/**
 * 1. 声明函数。这里建议显式的在声明文件中声明而不是通过头文件引用。这样有助于
 * 用户意外修改程序声明时，通过编译器发现错误。
 */

void move(float dist, uint16_t spd, uint8_t acc);
void arm_x_move(float dist, uint16_t spd, uint8_t acc);
void arm_z_move(float dist, uint16_t spd, uint8_t acc);
void arm_r_move(float dist, uint16_t spd, uint8_t acc);

/**
 * 2. 编写pcall。每一个函数调用对应一个pcall_item()
 * pcall_item()的第一个参数是函数名，第二个参数是函数的注释文档，第3/5/7...是函数参数
 * 第4/6/8...是函数参数对应的注释文档
 */

pcall_begin()
    pcall_item(move, "移动", float, "dist", uint16_t, "spd", uint16_t, "acc")
    pcall_item(arm_x_move, "x移动", float, "dist", uint16_t, "spd", uint16_t, "acc")
    pcall_item(arm_z_move, "y移动", float, "dist", uint16_t, "spd", uint8_t, "acc")
    pcall_item(arm_r_move, "r移动", float, "dist", uint16_t, "spd", uint8_t, "acc")
pcall_end()

/**
 * 3. 编写pcall表。每一个pcall对应一个pcall_table_item()
 * pcall_table_item()的第一个参数是函数调用对应的代码，单字符。第二个参数是函数的名称
 */

pcall_table_being()
    pcalll_table_item('m', move),
    pcalll_table_item('x', arm_x_move),
    pcalll_table_item('z', arm_z_move),
    pcalll_table_item('r', arm_r_move),
pcall_table_end()