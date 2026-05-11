#include "id_generator.hpp"
#include "database.hpp"
#include <random>
#include <string>

int randomInRange(int minimum, int maximum)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(minimum, maximum);
    return dist(mt);
}

std::string IdGenerator::generateId(const std::unordered_set<std::string> &ids)
{
    int id{};
    do
    {
        id = randomInRange(1, 999);

    } while (ids.count(std::to_string(id)));

    return std::to_string(id);
}
