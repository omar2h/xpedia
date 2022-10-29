#include "idGenerator.h"
#include "database.h"
#include <random>
#include <string>

int random_in_range(int minimum, int maximum)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(minimum, maximum);
    return dist(mt);
}

std::string IdGenerator::generate_id(const std::unordered_set<std::string> &ids)
{
    int id{};
    do
    {
        id = random_in_range(1, 999);

    } while (ids.count(std::to_string(id)));

    return std::to_string(id);
}
