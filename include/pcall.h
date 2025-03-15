#ifndef __PCALL_H__
#define __PCALL_H__

#include "pcall_class.h"

/**
 * @brief PCALL - Ptil0psis's Call - 简单的远程调用实现
 * @note 实现从字符串编码 'foo 100 200' 到二进制格式到函数调用 foo(100, 200)
 *            ----------------------  ---------- ---------------------
 *               用户指令(客户端)        传输用格式        服务端调用
 */

/**
 * @brief C/S使用不同的头文件实现，减少开销
 */
#ifdef __PCALL_CLIENT
#   include "pcall_cli.h"
#endif
#ifdef __PCALL_SERVER
#   include "pcall_srv.h"
#endif

/**
 * @brief 不应该在一个文件中同时使用Client和Server！
 */
#ifdef __PCALL_CLIENT
#   ifdef __PCALL_SERVER
        static_assert(false, "Client和Server不应该在同一个文件中存在！")
#   endif
#endif
#ifdef __PCALL_SERVER
#   ifdef __PCALL_CLIENT
        static_assert(false, "Client和Server不应该在同一个文件中存在！")
#   endif
#endif



/**
 * -声明相关---------------------------------------------------------------------
 */

/**
 * @note 将pcall实现放在一个匿名名字空间，避免产生的变量名污染
 */
#define pcall_begin() namespace {

/**
 * @brief 实现pcall
 */
#define pcall_item(_func, _desc, ...) \
        __pcall_impl(_func, _desc, __pcall_##_func, __pcall_count(__VA_ARGS__), __VA_ARGS__)

#define pcall_end() }


/**
 * @brief 实现pcall表构建
 */

#define pcall_table_being() namespace { ps::pcall::pcall PCALL_TABLE[] = {

/**
 * @brief pcall在表中注册
 */
#define pcalll_table_item(_ch, _func) __pcall_table_item(_ch, __pcall_##_func)
#ifdef __PCALL_CLIENT
#   define __pcall_table_item(_ch, _name) {_name, _name##_describe, _ch}
#else
#   define __pcall_table_item(_ch, _name) {_name}
#endif

#ifdef __PCALL_CLIENT // 加一避免零除！
#   define pcall_table_end() }; ps::pcall::Client pcall_init() {\
        return ps::pcall::Client {PCALL_TABLE,\
                                  sizeof(PCALL_TABLE)/sizeof(ps::pcall::pcall)};}}
#else
#   define pcall_table_end() }; ps::pcall::Server pcall_init() {\
        return ps::pcall::Server {PCALL_TABLE};}}
#endif

#endif 

