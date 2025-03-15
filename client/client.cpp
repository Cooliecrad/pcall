#include "client.h"

#define __PCALL_CLIENT
#include "mmcar_table.h"

#include <sstream>

static ps::pcall::Client client {pcall_init()};
static std::ostringstream oss;

int parse(const char *user, uint8_t *output, int lenght)
{
    return client.parse(std::string{user}, output, lenght);
}

int generate_help()
{
    std::vector<char> code_list;
    oss.clear();
    client.code_list(code_list);
    for (char code : code_list)
    {
        oss << code << ": " << client.describe(code) << '\n';
    }
    return oss.str().length() + 1; // 带上\0
}

void copy_help(char *buffer)
{
    auto len = oss.str().length();
    memcpy(buffer, oss.str().c_str(), len);
    buffer[len-1] = 0;
}