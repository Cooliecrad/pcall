#ifndef __PCALL_BASE_H__
#define __PCALL_BASE_H__

/**
 * @brief 基础的宏
 */

#define __pcall_wrap(x) (x)
#define __pcall_concat(a, b) a ## b

/* +UNPAK0 */
#define __pcall_count(...) __pcall_counter(9, ##__VA_ARGS__, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0)
#define __pcall_counter(_9, _8, __8, _7, __7, _6, __6, _5, __5, _4, __4, _3, __3, _2, __2, _1, __1, _0, __0, ...) __0
/* -UNPAK0 */

#define __pcall_length(_argc, ...) __pcall_concat(__pcall_length, _argc)(__VA_ARGS__)
#define __pcall_length0(...) (0)
/* +UNPAK1 */
#define __pcall_length1(_arg1, ...) (sizeof(_arg1)+(__pcall_length0(__VA_ARGS__)))
#define __pcall_length2(_arg2, ...) (sizeof(_arg2)+(__pcall_length1(__VA_ARGS__)))
#define __pcall_length3(_arg3, ...) (sizeof(_arg3)+(__pcall_length2(__VA_ARGS__)))
#define __pcall_length4(_arg4, ...) (sizeof(_arg4)+(__pcall_length3(__VA_ARGS__)))
#define __pcall_length5(_arg5, ...) (sizeof(_arg5)+(__pcall_length4(__VA_ARGS__)))
#define __pcall_length6(_arg6, ...) (sizeof(_arg6)+(__pcall_length5(__VA_ARGS__)))
#define __pcall_length7(_arg7, ...) (sizeof(_arg7)+(__pcall_length6(__VA_ARGS__)))
#define __pcall_length8(_arg8, ...) (sizeof(_arg8)+(__pcall_length7(__VA_ARGS__)))
/* -UNPAK1 */

#endif