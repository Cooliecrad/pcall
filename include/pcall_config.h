#ifndef __PCALL_CONFIG_H__
#define __PCALL_CONFIG_H__

#include <cstdint>

/**
 * -PCALL相关--------------------------------------------------------------------
 */

/**
 * @brief PCall号的数据类型，影响PCall的最大数量。建议使用无符号数
 */
using pcall_num_t = uint32_t;

/**
 * @brief 在服务器启用严格的长度检查
 */
#define __PCALL_SERVER_LENGTH_CHECK

/**
 * @brief 在客户端启用严格的长度检查
 */
#define __PCALL_CLIENT_LENGTH_CHECK

/**
 * -Code相关---------------------------------------------------------------------
 */

/**
 * @brief Code的最小值
 */
#define __PCALL_CODE_MINIMUM ' ' 

/**
 * @brief Code的最大值
 */
#define __PCALL_CODE_MAXIMUM '~'

static_assert(__PCALL_CODE_MAXIMUM > __PCALL_CODE_MINIMUM,
              "没有满足最小值小于最大值");

#endif