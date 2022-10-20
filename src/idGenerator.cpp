#include "idGenerator.h"
#include "database.h"
#include <chrono>
#include <random>
#include <string>

int random_in_range(int minimum, int maximum)
{
    thread_local std::ranlux48 rng(
        std::chrono::system_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(minimum, maximum)(rng);
}

std::string IdGenerator::generate_id(const std::unordered_set<std::string> &usersIds)
{
    int id{};
    do
    {
        id = random_in_range(100, 999);

    } while (usersIds.count(std::to_string(id)));

    return std::to_string(id);
}
