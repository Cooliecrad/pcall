#include "pcall.h"

void foo(int a, int b);

pcall_begin()
    pcall_item(foo, "Example function", int, "a:...", int, "b...")
pcall_end()

pcall_table_being()
    pcalll_table_item('f', foo)
pcall_table_end()