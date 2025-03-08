#ifndef __PS_CALL_H__
#include <cstdint>
#include <type_traits>

namespace ps
{

namespace pcode
{

struct pcall
{
    void( *call )(const void *user);
    const char *note;
};

template<typename __Tp>
using _call = void(*)(const __Tp*);

/**
 * @brief 调用函数装饰器，将要调用的函数包装成调用表所能使用的函数
 */
template<typename __Tp, _call<__Tp> __call>
struct wrapper
{
    wrapper(const char* note) : note {note} {}
    const char *note;
    static void call(const void *user) {__call((const __Tp*)user);}
    operator pcall() {return {wrapper::call, note};}
};

/**
 * @brief 调用表解析器，用来编码/解码调用表
 */
class PCallParser
{
public:
    using index_size_t = uint8_t; // 调用号的大小

    /**
     * @brief PCall解析器，自动按照调用表解析传入的数据
     */
    PCallParser(const pcall *call_table, int table_len)
        :call_table {call_table}, table_len {table_len} {}

    /**
     * @brief 解析并调用call_table中的函数
     */
    void parse(const void *user);
private:
    const pcall *call_table;
    const int table_len;
};

}

} 

#endif