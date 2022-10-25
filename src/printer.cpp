#include "printer.h"
#include "menuPrinter.h"
#include "itineraryItem.h"

#include <iostream>
void Printer::print_menu(const std::vector<std::string> &strings)
{
    MenuPrinter::print(strings);
}

void Printer::print_available_itinerary_items(const std::vector<ItineraryItem *> &items)
{
    int count = (int)items.size();
    int choice{};
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << ": " << items[i]->toString() << "\n";
    }
    std::cout << "Enter choice(-1 to cancel): ";
}

void Printer::print_options(const std::vector<PaymentCard> &cards)
{
    int count{(int)cards.size()};
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << ": " << cards[i].toString() << "\n";
    }
    std::cout << "Enter choice(0 to add card, -1 to cancel): ";
}
