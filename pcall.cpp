#include "pcall.h"

using namespace ps::pcode;

/**
 * @brief 序列化的调用数据结构
 */
struct pcall_serialize
{
    PCallParser::index_size_t call_index; // 调用号，由解析器自动指定
    const void *user; // 用户数据
};

void PCallParser::parse(const void *user)
{
    auto serialize = (const pcall_serialize*)user;
    if (serialize->call_index < table_len)
    {
        call_table[serialize->call_index].call(serialize->user);
    }
}