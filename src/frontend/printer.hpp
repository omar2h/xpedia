#pragma once

#include <vector>
#include <string>
#include "../model/payment_card.hpp"

class ItineraryItem;
class Printer
{

public:
    static void printMenu(const std::vector<std::string> &);
    static void printOptions(const std::vector<std::string> &);
};
