#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

/**
 * @brief 简单的C语言测试程序
 */
int main(void)
{
    int _size = generate_help();
    printf("%d", _size);
    char *buffer = (char*)malloc(_size);
    copy_help(buffer);
    
    char user[128];
    std::cin.getline(user, 128);
    uint8_t output[128] = {0};
    parse(user, output, 128);
    printf("%s", buffer);
}