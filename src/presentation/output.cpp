#include "output.hpp"
#include <iostream>

void ConsoleOutput::write(const std::string& msg)
{
    std::cout << msg << std::flush;
}

void ConsoleOutput::writeLine(const std::string& msg)
{
    std::cout << msg << "\n";
}
