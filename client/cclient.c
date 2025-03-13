#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 简单的C语言测试程序
 */
int main(void)
{
    int _size = generate_help();
    printf("%d", _size);
    char *buffer = (char*)malloc(_size);
    copy_help(buffer);
    printf("%s", buffer);
}