#ifndef __PCALL_CLI_H__
#define __PCALL_CLI_H__

#include "pcall_base.h"

/**
 * @brief pcall客户端实现
 */

#define __pcall_pak(_src, _dst, _argc, ...) __pcall_concat(__pcall_pak, _argc)(_src, _dst, __VA_ARGS__)
#define __pcall_pak0(_src, _dst, ...)
/* +UNPAK0 */
#define __pcall_pak1(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak2(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak3(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak4(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak5(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak6(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak7(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
#define __pcall_pak8(_src, _dst, _arg, ...) \
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);
/* -UNPAK0 */

#ifdef __PCALL_CLIENT_LENGTH_CHECK
#define __PCALL_LENGTH_CHECK(_argc, ...) \
    if (length < (__pcall_length(_argc, __VA_ARGS__))) return 0
#else
#define __PCALL_LENGTH_CHECK(...) 
#endif

/**
 * @brief 调用方编码数据的实现
 */
#define __pcall_func_impl(_func, _func_name, _argc, ...) \
int _func_name(std::istringstream& iss, uint8_t *data, int length) \
{ \
    __PCALL_LENGTH_CHECK(_argc, __VA_ARGS__); \
    __pcall_pak(iss, data, _argc, __VA_ARGS__) \
    return (__pcall_length(_argc, __VA_ARGS__)); \
}

/**
 * @brief 将pcall宏中__VA_ARGS__拆开成参数和注释，产生对应的函数和注释文本
 */
#define __pcall_impl(_func, _desc, _func_name, _argc, ...) \
        __pcall_concat(__pcall_impl, _argc)(_func, _desc, _func_name,\
                                            _argc, __VA_ARGS__)
#define __pcall_impl0(_func, _desc, _func_name, _argc) \
        const char * _func_name##_describe = _desc##;
/* +UNPAK1 */
#define __pcall_impl1(_func, _desc, _func_name, _argc, _arg1, _desc1)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n";
#define __pcall_impl2(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n";
#define __pcall_impl3(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n";
#define __pcall_impl4(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n"#_arg4 ": " _desc4 " \n";
#define __pcall_impl5(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n"#_arg4 ": " _desc4 " \n"#_arg5 ": " _desc5 " \n";
#define __pcall_impl6(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n"#_arg4 ": " _desc4 " \n"#_arg5 ": " _desc5 " \n"#_arg6 ": " _desc6 " \n";
#define __pcall_impl7(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6, _arg7, _desc7)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _arg7)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n"#_arg4 ": " _desc4 " \n"#_arg5 ": " _desc5 " \n"#_arg6 ": " _desc6 " \n"#_arg7 ": " _desc7 " \n";
#define __pcall_impl8(_func, _desc, _func_name, _argc, _arg1, _desc1, _arg2, _desc2, _arg3, _desc3, _arg4, _desc4, _arg5, _desc5, _arg6, _desc6, _arg7, _desc7, _arg8, _desc8)\
        __pcall_func_impl(_func, _func_name, _argc, _arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _arg7, _arg8)\
        const char * _func_name##_describe = _desc ":\n" #_arg1 ": " _desc1 " \n"#_arg2 ": " _desc2 " \n"#_arg3 ": " _desc3 " \n"#_arg4 ": " _desc4 " \n"#_arg5 ": " _desc5 " \n"#_arg6 ": " _desc6 " \n"#_arg7 ": " _desc7 " \n"#_arg8 ": " _desc8 " \n";
/* -UNPAK1 */

#endif
