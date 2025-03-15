#ifndef __PCALL_SRV_H__
#define __PCALL_SRV_H__

#include "pcall_base.h"
#include <cstring>

/**
 * @brief pcall服务端实现
 * @note 为什么要使用memcpy？指针解引用会有内存不对齐的隐患，所以必须手动模拟内存拷贝
 */

#define __pcall_unpak(_func, _argc, ...) __pcall_concat(__pcall_unpak, _argc)(_func, __VA_ARGS__)
#define __pcall_unpak0(_func, ...)
/* +UNPAK0 */
#define __pcall_unpak1(_func, _arg1, ...) \
    _arg1 tmp1; memcpy(&tmp1, data, sizeof(_arg1)); data += sizeof(_arg1);\
    __pcall_unpak0(_func, __VA_ARGS__)
#define __pcall_unpak2(_func, _arg2, ...) \
    _arg2 tmp2; memcpy(&tmp2, data, sizeof(_arg2)); data += sizeof(_arg2);\
    __pcall_unpak1(_func, __VA_ARGS__)
#define __pcall_unpak3(_func, _arg3, ...) \
    _arg3 tmp3; memcpy(&tmp3, data, sizeof(_arg3)); data += sizeof(_arg3);\
    __pcall_unpak2(_func, __VA_ARGS__)
#define __pcall_unpak4(_func, _arg4, ...) \
    _arg4 tmp4; memcpy(&tmp4, data, sizeof(_arg4)); data += sizeof(_arg4);\
    __pcall_unpak3(_func, __VA_ARGS__)
#define __pcall_unpak5(_func, _arg5, ...) \
    _arg5 tmp5; memcpy(&tmp5, data, sizeof(_arg5)); data += sizeof(_arg5);\
    __pcall_unpak4(_func, __VA_ARGS__)
#define __pcall_unpak6(_func, _arg6, ...) \
    _arg6 tmp6; memcpy(&tmp6, data, sizeof(_arg6)); data += sizeof(_arg6);\
    __pcall_unpak5(_func, __VA_ARGS__)
#define __pcall_unpak7(_func, _arg7, ...) \
    _arg7 tmp7; memcpy(&tmp7, data, sizeof(_arg7)); data += sizeof(_arg7);\
    __pcall_unpak6(_func, __VA_ARGS__)
#define __pcall_unpak8(_func, _arg8, ...) \
    _arg8 tmp8; memcpy(&tmp8, data, sizeof(_arg8)); data += sizeof(_arg8);\
    __pcall_unpak7(_func, __VA_ARGS__)
/* -UNPAK0 */

#define __pcall_execute(_func, _argc) __pcall_concat(__pcall_execute, _argc)(_func)
#define __pcall_execute0(_func) _func();
/* +UNPAK1 */
#define __pcall_execute1(_func) _func(tmp1);
#define __pcall_execute2(_func) _func(tmp2, tmp1);
#define __pcall_execute3(_func) _func(tmp3, tmp2, tmp1);
#define __pcall_execute4(_func) _func(tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute5(_func) _func(tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute6(_func) _func(tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute7(_func) _func(tmp7, tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);
#define __pcall_execute8(_func) _func(tmp8, tmp7, tmp6, tmp5, tmp4, tmp3, tmp2, tmp1);
/* -UNPAK1 */


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

/**
 * @brief 将pcall宏中__VA_ARGS__拆开成参数和注释，产生对应的函数和注释文本
 */
#define __pcall_impl(_func, _desc, _func_name, _argc, ...) \
        __pcall_concat(__pcall_impl, _argc)(_func, _desc, _func_name,\
                                            _argc, __VA_ARGS__)
#define __pcall_impl0(_func, _desc, _func_name, _argc) \
        const char * _func_name##_describe = _desc##;
/* +UNPAK2 */
#define __pcall_impl1(_func, _desc, _func_name, _argc, _arg1, _desc1)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1)
#define __pcall_impl2(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2)
#define __pcall_impl3(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3)
#define __pcall_impl4(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4)
#define __pcall_impl5(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5)
#define __pcall_impl6(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6)
#define __pcall_impl7(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6, _arg7, _desc7)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _arg7)
#define __pcall_impl8(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6, _arg7, _desc7, _arg8, _desc8)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _arg7, _arg8)
/* -UNPAK2 */
#endif
