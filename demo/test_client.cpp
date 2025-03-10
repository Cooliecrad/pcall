#define __PCALL_CLIENT
#include "test.h"
#include "test_table.h"
#include <string>

void test_client(const char *src, uint8_t *dst)
{
    std::string str {src};
    auto client = pcall_init();
    // std::vector<char> code_list;
    // client.code_list(code_list);
    // for (char ch : code_list) printf("%c: %s\n", ch, client.describe(ch));
    client.parse(str, dst, 120);
}