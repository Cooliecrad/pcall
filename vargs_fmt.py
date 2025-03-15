def replace_content(src: str, index: int, content: str) -> str:
    """找到src中 /* +UNPAK{index} */ 和 /* -UNPAK{index} */ 之间的内容，
    并且用content替换

    Args:
        src (str): 原始内容
        index (int): 要替换的下标
        content (str): 要替换的内容

    Returns:
        str: 替换完的内容
    """
    start_label = f"/* +UNPAK{index} */"
    end_label = f"/* -UNPAK{index} */"
    start_index = src.index(start_label) + len(start_label)
    end_index = src.index(end_label)
    return src[:start_index] + '\n' + content + src[end_index:]

# pcall_base.h -----------------------------------------------------------------

def pcall_base(src, length) -> str:
    src = replace_content(src, 0, gen_counter(length))
    return replace_content(src, 1, gen_length(length))

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
    result = ""
    for x in range(1, length+1):
        result += f"#define __pcall_length{x}(_arg{x}, ...) (sizeof(_arg{x})+(__pcall_length{x-1}(__VA_ARGS__)))\n"
    return result

# pcall_cli.h ------------------------------------------------------------------

def pcall_cli(src, length) -> str:
    src = replace_content(src, 0, __pcall_pak(length))
    return replace_content(src, 1, __pcall_impl(length, True))

def __pcall_impl(length, client):
    result = ""
    for x in range(1, length+1):
        line0 = f"#define __pcall_impl{x}(_func, _desc, _func_name, _argc"
        line1 = f"        __pcall_func_impl(_func, _func_name, _argc"
        line2_l = f'        const char * _func_name##_describe = _desc ":\\n" '
        line2_r = ""
        for index in range(1, x+1):
            line0 += f", _arg{index}, _desc{index}"
            line1 += f", _arg{index}"
            line2_r += f'#_arg{index} ": " _desc{index} " \\n"'
        line0 += ")"
        line1 += ")"
        line2_r += ";"
        if client:
            result += line0 + "\\\n" + line1 + "\\\n" + line2_l + line2_r + "\n"
        else:
            result += line0 + "\\\n" + line1 + "\n"
    return result

def __pcall_pak(length):
    result = ""
    for x in range(1, length+1):
        result += f"\
#define __pcall_pak{x}(_src, _dst, _arg, ...) \\\n\
    _arg tmp; _src >> tmp; memcpy(data, &tmp, sizeof(_arg)); _dst += sizeof(_arg);\n"
    return result

# pcall_srv.h ------------------------------------------------------------------

def pcall_srv(src, length):
    src = replace_content(src, 0, __pcall_unpak(length))
    src = replace_content(src, 1, __pcall_execute(length))
    src = replace_content(src, 2, __pcall_impl(length, False))
    return src

def __pcall_execute(length):
    result = ""
    for x in range(1, length+1):
        result += f"#define __pcall_execute{x}(_func) _func("
        for index in range(x, 1, -1):
            result += f"tmp{index}, "
        result += f"tmp1);\n"
    return result

def __pcall_unpak(length):
    result = ""
    for x in range(1, length+1):
        result += f"\
#define __pcall_unpak{x}(_func, _arg{x}, ...) \\\n\
    _arg{x} tmp{x}; memcpy(&tmp{x}, data, sizeof(_arg{x})); data += sizeof(_arg{x});\\\n\
    __pcall_unpak{x-1}(_func, __VA_ARGS__)\n"
    return result

def write(func, length, suffix):
    with open(f"include/pcall{suffix}.h", "r", encoding='utf-8') as fp:
        src = fp.read()
    
    src = func(src, length)
    with open(f"build/pcall{suffix}.h", "w", encoding='utf-8') as fp:
        fp.write(src)

if __name__ == "__main__":
    length = 8
    write(pcall_base, 8, "_base")
    write(pcall_cli, 8, "_cli")
    write(pcall_srv, 8, "_srv")