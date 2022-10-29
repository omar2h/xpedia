#ifndef __IDGENERATOR_H__
#define __IDGENERATOR_H__
#include <string>
#include <unordered_set>
class IdGenerator
{
public:
    static std::string generate_id(const std::unordered_set<std::string> &);
};
#endif // __IDGENERATOR_H__