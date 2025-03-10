#ifndef __PCALL_CLI_H__
#define __PCALL_CLI_H__

#include "pcall_base.h"

/**
 * @brief pcall客户端实现
 */

#define __pcall_pak(_src, _dst, _argc, ...) __pcall_concat(__pcall_pak, _argc)(_src, _dst, __VA_ARGS__)
#define __pcall_pak0(_src, _dst, ...)
#define __pcall_pak1(_src, _dst, _arg1, ...) _src >> ((_arg1&)*_dst); _dst += sizeof(_arg1);\
                                             __pcall_pak0(_src, _dst, __VA_ARGS__)
#define __pcall_pak2(_src, _dst, _arg2, ...) _src >> ((_arg2&)*_dst); _dst += sizeof(_arg2);\
                                             __pcall_pak1(_src, _dst, __VA_ARGS__)
#define __pcall_pak3(_src, _dst, _arg3, ...) _src >> ((_arg3&)*_dst); _dst += sizeof(_arg3);\
                                             __pcall_pak2(_src, _dst, __VA_ARGS__)
#define __pcall_pak4(_src, _dst, _arg4, ...) _src >> ((_arg4&)*_dst); _dst += sizeof(_arg4);\
                                             __pcall_pak3(_src, _dst, __VA_ARGS__)
#define __pcall_pak5(_src, _dst, _arg5, ...) _src >> ((_arg5&)*_dst); _dst += sizeof(_arg5);\
                                             __pcall_pak4(_src, _dst, __VA_ARGS__)
#define __pcall_pak6(_src, _dst, _arg6, ...) _src >> ((_arg6&)*_dst); _dst += sizeof(_arg6);\
                                             __pcall_pak5(_src, _dst, __VA_ARGS__)
#define __pcall_pak7(_src, _dst, _arg7, ...) _src >> ((_arg7&)*_dst); _dst += sizeof(_arg7);\
                                             __pcall_pak6(_src, _dst, __VA_ARGS__)
#define __pcall_pak8(_src, _dst, _arg8, ...) _src >> ((_arg8&)*_dst); _dst += sizeof(_arg8);\
                                             __pcall_pak7(_src, _dst, __VA_ARGS__)


#ifdef __PCALL_CLIENT_LENGTH_CHECK
#define __PCALL_LENGTH_CHECK(_argc, ...) \
    if (length < (__pcall_length(_argc, __VA_ARGS__))) return false
#else
#define __PCALL_LENGTH_CHECK(...) 
#endif

/**
 * @brief 调用方编码数据的实现
 */
#define __pcall_func_impl(_func, _func_name, _argc, ...) \
bool _func_name(std::istringstream& iss, uint8_t *data, int length) \
{ \
    __PCALL_LENGTH_CHECK(_argc, __VA_ARGS__); \
    __pcall_pak(iss, data, _argc, __VA_ARGS__) \
    return true; \
}

#endif
