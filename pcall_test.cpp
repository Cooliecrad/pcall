#include "pcall.h"
#include <cstdio>

using namespace ps::pcode;

struct Point2i
{
    int x;
    int y;
};

struct Point2f
{
    float x;
    float y;
};

struct simulate_call
{
    PCallParser::index_size_t index;
    void *user;
};

void test_p2i(const Point2i* p2i)
{
    printf("test_p2i: %d, %d\n", p2i->x, p2i->y);
}

void test_p2f(const Point2f* p2i)
{
    printf("test_p2f: %f, %f\n", p2i->x, p2i->y);
}
const static pcall pcall_table[] = {
    wrapper<Point2i, test_p2i>{""},
    wrapper<Point2f, test_p2f>{""}
};

int main(void)
{
    // 构造解释器
    PCallParser parser {pcall_table, sizeof(pcall_table)/sizeof(pcall)};

    // 构造两个数据结构
    Point2i p2i {1, 2};
    simulate_call sp2i {0, (void*)&p2i};
    Point2f p2f {1, 2};
    simulate_call sp2f {1, (void*)&p2f};
    
    // 尝试解析
    parser.parse((void*)&sp2i);
    parser.parse((void*)&sp2f);
}