#ifndef __PCALL_CLASS_H__
#define __PCALL_CLASS_H__


#include <cstdint>
#include <cstring>

#ifdef __PCALL_CLIENT
#   include <vector>
#   include <sstream>
#endif

/**
 * @brief pcall的C/S模型
 */

namespace ps
{
namespace pcall
{

#include "pcall_config.h"

/**
 * @brief 将编码/解码以及注释混合在同一个数据结构中，后续的宏操作便不需要关注具体的函数实现了
 */
struct pcall
{
#   ifdef __PCALL_CLIENT
        bool (*enc)(std::istringstream& iss, uint8_t *data, int length);
        const char *note;
        const char code;

#       ifdef __PCALL_CLIENT_LENGTH_CHECK
            const int length;
#       endif
#   endif

#   ifdef __PCALL_SERVER
        bool (*dec)(const uint8_t *data, int length);

#       ifdef __PCALL_SERVER_LENGTH_CHECK
            const int length;
#       endif
#   endif


};

#ifdef __PCALL_CLIENT
class Client
{
public:
    Client(const pcall *pc, pcall_num_t size)
        : pc {pc}
    {
        /**
         * @note pcall号是pcall表中下标+1
         */
        map = new pcall_num_t[__PCALL_CODE_MAXIMUM - __PCALL_CODE_MINIMUM + 2];
        memset(map, 0, sizeof(pcall_num_t)*(__PCALL_CODE_MAXIMUM-__PCALL_CODE_MINIMUM+2)); // 如果下标是0，认为没有这个元素
        for (int x=0; x<size; x++)
        {
            map[pc[x].code - __PCALL_CODE_MINIMUM] = x + 1;
        }
    }

    /**
     * @brief 解析单个指令
     */
    bool parse(const std::string& src, uint8_t *dst, int length) const
    {
        std::istringstream iss {src};
        // 读取code
        char code;
        iss >> code;
        // 读取map获得pcall号
        pcall_num_t number = map[code - __PCALL_CODE_MINIMUM];
        if (number != 0) // 如果是-1，说明这个元素是无效的
        {
            *((pcall_num_t*)dst) = number; // 包头：pcall号
            dst += sizeof(pcall_num_t); // 记得移动指针 
            // 通过pcall号调用编码函数
            return pc[number-1].enc(iss, dst, length);
        }
        return false;
    }

    /**
     * @brief 返回指定code的描述
     */
    const char* describe(char code) const
    {
        auto number = map[code - __PCALL_CODE_MINIMUM];
        if (number != 0)
        {
            return pc[number-1].note;
        }
        return nullptr;
    }

    /**
     * @brief 返回code个数
     */
    pcall_num_t code_num() const
    {
        pcall_num_t ret = 0;
        for (int x=0; x < __PCALL_CODE_MAXIMUM - __PCALL_CODE_MINIMUM + 2; x++)
        {
            if (map[x] != 0) ret++;
        }
        return ret;
    }

    /**
     * @brief 返回保存了所有code号的数组
     */
    void code_list(std::vector<char>& result)
    {
        for (int x=0; x< __PCALL_CODE_MAXIMUM - __PCALL_CODE_MINIMUM + 2; x++)
        {
            if (map[x] != 0) result.push_back((char)(x + __PCALL_CODE_MINIMUM));
        }
    }

private:
    const pcall *pc; // pcall号-pcall表
    pcall_num_t *map; // pcode-pcall号 表
};
#endif

#ifdef __PCALL_SERVER
class Server
{
public:
    Server(const pcall *pc) : pc {pc} {}
    bool parse(const uint8_t *dst, int length) {
        pcall_num_t number = *((pcall_num_t*)dst);
        if (number != 0)
        {
            dst += sizeof(pcall_num_t);
            // 通过pcall号调用函数
            pc[number-1].dec(dst, length);
            return true;
        }
        return false;
    }
private:
    const pcall *pc;
};
#endif

}
}

#endif