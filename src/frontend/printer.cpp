#include "printer.h"
#include "menuPrinter.h"
#include "../model/itineraryItem.h"

#include <iostream>
void Printer::print_menu(const std::vector<std::string> &strings)
{
    MenuPrinter::print(strings);
}

void Printer::print_options(const std::vector<std::string> &options)
{
    int count{(int)options.size()};
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << ": " << options[i] << "\n";
    }
}
