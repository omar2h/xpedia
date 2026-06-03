#include "id_generator.hpp"
#include <iomanip>
#include <random>
#include <sstream>

std::string generateId()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    for (int i = 0; i < 32; ++i)
    {
        if (i == 8 || i == 12 || i == 16 || i == 20)
        {
            ss << '-';
        }
        ss << std::hex << dis(gen);
    }
    return ss.str();
}