#include "id_generator.hpp"
#include <random>
#include <sstream>
#include <iomanip>

static std::mt19937 &rng()
{
    static std::mt19937 mt{std::random_device{}()};
    return mt;
}

static std::string hex8()
{
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << dist(rng());
    return oss.str();
}

std::string generateId()
{
    std::ostringstream oss;
    // UUID v4 format: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
    oss << hex8() << "-"
        << hex8().substr(0, 4) << "-4" << hex8().substr(0, 3) << "-"
        << std::hex << (8 + std::uniform_int_distribution<int>(0, 3)(rng()))
        << hex8().substr(0, 3) << "-"
        << hex8() << hex8();
    return oss.str();
}
