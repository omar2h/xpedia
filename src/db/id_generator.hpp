#pragma once

#include <string>
#include <unordered_set>
class IdGenerator
{
public:
    static std::string generate_id(const std::unordered_set<std::string> &);
};
