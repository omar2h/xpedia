#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include <string>
#include "paymentCard.h"
class ItineraryItem;
class Printer
{

public:
    static void print_menu(const std::vector<std::string> &);
    static void print_available_itinerary_items(const std::vector<ItineraryItem *> &);
    static void print_options(const std::vector<PaymentCard> &);
};
#endif // __PRINTER_H__