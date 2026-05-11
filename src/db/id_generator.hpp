#pragma once

#include <string>
#include <unordered_set>
class IdGenerator
{
public:
    static std::string generateId(const std::unordered_set<std::string> &);
};
