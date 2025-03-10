#ifndef __PCALL_SRV_H__
#define __PCALL_SRV_H__

#include "pcall_base.h"

/**
 * @brief pcall服务端实现
 */

#define __pcall_unpak(_func, _argc, ...) __pcall_concat(__pcall_unpak, _argc)(_func, __VA_ARGS__)
#define __pcall_unpak0(_func, ...)
#define __pcall_unpak1(_func, _arg1, ...) \
    _arg1 tmp1 = *(_arg1*)data; data += sizeof(_arg1);\
    __pcall_unpak0(_func, __VA_ARGS__)
#define __pcall_unpak2(_func, _arg2, ...) \
    _arg2 tmp2 = *(_arg2*)data; data += sizeof(_arg2);\
    __pcall_unpak1(_func, __VA_ARGS__)
#define __pcall_unpak3(_func, _arg3, ...) \
    _arg3 tmp3 = *(_arg3*)data; data += sizeof(_arg3);\
    __pcall_unpak2(_func, __VA_ARGS__)
#define __pcall_unpak4(_func, _arg4, ...) \
    _arg4 tmp4 = *(_arg4*)data; data += sizeof(_arg4);\
    __pcall_unpak3(_func, __VA_ARGS__)
#define __pcall_unpak5(_func, _arg5, ...) \
    _arg5 tmp5 = *(_arg5*)data; data += sizeof(_arg5);\
    __pcall_unpak4(_func, __VA_ARGS__)
#define __pcall_unpak6(_func, _arg6, ...) \
    _arg6 tmp6 = *(_arg6*)data; data += sizeof(_arg6);\
    __pcall_unpak5(_func, __VA_ARGS__)
#define __pcall_unpak7(_func, _arg7, ...) \
    _arg7 tmp7 = *(_arg7*)data; data += sizeof(_arg7);\
    __pcall_unpak6(_func, __VA_ARGS__)
#define __pcall_unpak8(_func, _arg8, ...) \
    _arg8 tmp8 = *(_arg8*)data; data += sizeof(_arg8);\
    __pcall_unpak7(_func, __VA_ARGS__)

#define __pcall_execute(_func, _argc) __pcall_concat(__pcall_execute, _argc)(_func)
#define __pcall_execute0(_func) _func();
#define __pcall_execute1(_func) _func(tmp1);
#define __pcall_execute2(_func) _func(tmp2, tmp1);
#define __pcall_execute3(_func) _func(tmp3, tmp2, tmp1);
#define __pcall_execute4(_func) _func(tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute5(_func) _func(tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute6(_func) _func(tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute7(_func) _func(tmp7, tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute8(_func) _func(tmp8, tmp7, tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);


#ifdef __PCALL_SERVER_LENGTH_CHECK
#define __PCALL_LENGTH_CHECK(_argc, ...) \
    if (length < (__pcall_length(_argc, __VA_ARGS__))) return false
#else
#define __PCALL_LENGTH_CHECK(...) 
#endif

/**
 * @brief 被调用方解码并执行的实现
 */
#define __pcall_func_impl(_func, _func_name, _argc, ...) \
bool _func_name(const uint8_t *data, int length) \
{ \
    __PCALL_LENGTH_CHECK(_argc, __VA_ARGS__); \
    __pcall_unpak(_func, _argc, __VA_ARGS__) \
    __pcall_execute(_func, _argc) \
    return true; \
}

#endif
