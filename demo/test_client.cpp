/**
 * @brief 最重要的部分：声明本文件为服务器（第四行）和引用共享的头文件（第五行）
 */
#define __PCALL_CLIENT
#include "test_table.h"

#include "test.h"
#include <string>

/**
 * @brief 客户端处理用户传入的字符串(src)并且转换成中间格式(dst)。转换期间还打印了帮助文档
 */
void test_client(const char *src, uint8_t *dst)
{
    // 转换数据
    std::string str {src};
    auto client = pcall_init();
    client.parse(str, dst, 120);

    // 打印帮助文档
    std::vector<char> code_list;
    client.code_list(code_list);
    for (char ch : code_list) printf("%c: %s\n", ch, client.describe(ch));
}