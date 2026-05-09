#pragma once

#include <vector>
#include <string>
#include "../model/payment_card.hpp"

class ItineraryItem;
class Printer
{

public:
    static void print_menu(const std::vector<std::string> &);
    static void print_options(const std::vector<std::string> &);
};
