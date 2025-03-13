#ifndef __PCALL_EXAMPLE_CLIENT_H__
#define __PCALL_EXAMPLE_CLIENT_H__

#include <stdint.h>

/**
 * @brief 为Python调用设计的简单示例程序
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 解析用户的输入，产生用于传输的中间数据格式
 * @param user 用户的字符串输入
 * @param output 用来保存用户输出
 * @param length 输出数组的长度
 * @return 如果超长，将不会输出
 */
int parse(const char *user, uint8_t *output, int length);

/**
 * @brief 生成帮助文档，获得接收帮助文档需要的长度
 */
int generate_help();

/**
 * @brief 拷贝帮助文档到指定的数组中
 * @param buffer 必须放在buffer中
 */
void copy_help(char *buffer);

#ifdef __cplusplus
}
#endif


#endif