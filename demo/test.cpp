#include "test.h"

/**
 * @brief 模拟代码-解析(上位机)-传输(上位机->下位机)-调用(下位机)
 */

int main(void)
{
    uint8_t buffer[128] = {0};

    test_client("m 1.5 100 10", buffer); // 自动将 m 1.5 100 200 转换成便于传输的格式，
                                          // 保存到buffer中

    test_server(buffer); // 自动解析中间格式，并完成调用
}