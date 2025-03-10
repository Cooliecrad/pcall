from sys import argv

def pcall_base(length) -> str:
    result = """#ifndef __PCALL_BASE_H__
#define __PCALL_BASE_H__

/**
 * @brief 基础的宏
 */

#define __pcall_wrap(x) (x)
#define __pcall_concat(a, b) a ## b

"""
    result += gen_counter(length) + "\n"
    result += gen_length(length) + "\n"
    result += "#endif"
    return result

def gen_counter(length):
    count = f"#define __pcall_count(...) __pcall_counter({length+1}, ##__VA_ARGS__, "
    for x in range(length, 0, -1):
        count += f"{x}, {x}, "
    count += "0, 0)\n"

    counter = f"#define __pcall_counter(_{length+1}, "
    for x  in range(length, 0, -1):
        counter += f"_{x}, __{x}, "
    counter += "_0, __0, ...) __0\n"
    return count + counter

def gen_length(length):
    result = """#define __pcall_length(_argc, ...) __pcall_concat(__pcall_length, _argc)(__VA_ARGS__)
#define __pcall_length0(...) (0)
"""
    for x in range(1, length+1):
        result += f"#define __pcall_length{x}(_arg{x}, ...) (sizeof(_arg{x})+(__pcall_length{x-1}(__VA_ARGS__)))\n"
    return result

def pcall_cli(length) -> str:
    result = """#ifndef __PCALL_CLI_H__
#define __PCALL_CLI_H__

#include "pcall_base.h"

/**
 * @brief pcall客户端实现
 */

"""
    result += __pcall_pak(length)
    result += """

#ifdef __PCALL_CLIENT_LENGTH_CHECK
#define __PCALL_LENGTH_CHECK(_argc, ...) \\
    if (length < (__pcall_length(_argc, __VA_ARGS__))) return false
#else
#define __PCALL_LENGTH_CHECK(...) 
#endif

/**
 * @brief 调用方编码数据的实现
 */
#define __pcall_func_impl(_func, _func_name, _argc, ...) \\
bool _func_name(std::istringstream& iss, uint8_t *data, int length) \\
{ \\
    __PCALL_LENGTH_CHECK(_argc, __VA_ARGS__); \\
    __pcall_pak(iss, data, _argc, __VA_ARGS__) \\
    return true; \\
}

#endif
"""
    return result

def __pcall_pak(length):
    result = "#define __pcall_pak(_src, _dst, _argc, ...) __pcall_concat(__pcall_pak, _argc)(_src, _dst, __VA_ARGS__)\n#define __pcall_pak0(_src, _dst, ...)\n"
    for x in range(1, length+1):
        result += f"\
#define __pcall_pak{x}(_src, _dst, _arg{x}, ...) _src >> ((_arg{x}&)*_dst); _dst += sizeof(_arg{x});\\\n\
                                             __pcall_pak{x-1}(_src, _dst, __VA_ARGS__)\n"
    return result


def pcall_srv(length):
    result = """#ifndef __PCALL_SRV_H__
#define __PCALL_SRV_H__

#include "pcall_base.h"

/**
 * @brief pcall服务端实现
 */

"""
    result += __pcall_unpak(length) + "\n"
    result += __pcall_execute(length) + "\n"
    result += """
#ifdef __PCALL_SERVER_LENGTH_CHECK
#define __PCALL_LENGTH_CHECK(_argc, ...) \\
    if (length < (__pcall_length(_argc, __VA_ARGS__))) return false
#else
#define __PCALL_LENGTH_CHECK(...) 
#endif

/**
 * @brief 被调用方解码并执行的实现
 */
#define __pcall_func_impl(_func, _func_name, _argc, ...) \\
bool _func_name(const uint8_t *data, int length) \\
{ \\
    __PCALL_LENGTH_CHECK(_argc, __VA_ARGS__); \\
    __pcall_unpak(_func, _argc, __VA_ARGS__) \\
    __pcall_execute(_func, _argc) \\
    return true; \\
}

#endif
"""
    return result

def __pcall_execute(length):
    result = "#define __pcall_execute(_func, _argc) __pcall_concat(__pcall_execute, _argc)(_func)\n#define __pcall_execute0(_func) _func();\n"
    for x in range(1, length+1):
        result += f"#define __pcall_execute{x}(_func) _func("
        for index in range(x, 1, -1):
            result += f"tmp{index}, "
        result += f"tmp{1});\n"
    return result

def __pcall_unpak(length):
    result = "\
#define __pcall_unpak(_func, _argc, ...) __pcall_concat(__pcall_unpak, _argc)(_func, __VA_ARGS__)\n\
#define __pcall_unpak0(_func, ...)\n"
    for x in range(1, length+1):
        result += f"\
#define __pcall_unpak{x}(_func, _arg{x}, ...) \\\n\
    _arg{x} tmp{x} = *(_arg{x}*)data; data += sizeof(_arg{x});\\\n\
    __pcall_unpak{x-1}(_func, __VA_ARGS__)\n"
    return result


def pcall(length):
    result = """#ifndef __PCALL_H__
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
 * @brief 将pcall宏中__VA_ARGS__拆开成参数和注释，产生对应的函数和注释文本
 */
"""
    result += __pcall_impl(length)
    result += """/**
 * -声明相关---------------------------------------------------------------------
 */

/**
 * @note 将pcall实现放在一个匿名名字空间，避免产生的变量名污染
 */
#define pcall_begin() namespace {

/**
 * @brief 实现pcall
 */
#define pcall_item(_func, _desc, ...) \\
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
#   define pcall_table_end() }; ps::pcall::Client pcall_init() {\\
        return ps::pcall::Client {PCALL_TABLE,\\
                                  sizeof(PCALL_TABLE)/sizeof(ps::pcall::pcall)};}}
#else
#   define pcall_table_end() }; ps::pcall::Server pcall_init() {\\
        return ps::pcall::Server {PCALL_TABLE};}}
#endif

#endif 

"""
    return result

def __pcall_impl(length):
    result = f'\
#define __pcall_impl(_func, _desc, _func_name, _argc, ...) \\\n\
        __pcall_concat(__pcall_impl, _argc)(_func, _desc, _func_name,\\\n\
                                            _argc, __VA_ARGS__)\n\
#define __pcall_impl0(_func, _desc, _func_name, _argc) \\\n\
        const char * _func_name##_describe = _desc##;\n'
    for x in range(1, length+1):
        line0 = f"#define __pcall_impl{x}(_func, _desc, _func_name, _argc"
        line1 = f"        __pcall_func_impl(_func, _func_name, _argc"
        line2_l = f'        const char * _func_name##_describe = _desc ":\\n" '
        line2_r = ""
        for index in range(1, x+1):
            line0 += f", _arg{index}, _desc{index}"
            line1 += f", _arg{index}"
            line2_r += f'#_arg{index} ": " _desc{index} " \\n"'
        line0 += ")\\\n"
        line1 += ")\\\n"
        line2_r += ";\n"
        result += line0 + line1 + line2_l + line2_r
    return result

def write(func, length, suffix):
    with open(f"build/pcall{suffix}.h", "w", encoding='utf-8') as fp:
        fp.write(func(length))

if __name__ == "__main__":
    length = 8
    write(pcall_base, 8, "_base")
    write(pcall_cli, 8, "_cli")
    write(pcall_srv, 8, "_srv")
    write(pcall, 8, "")