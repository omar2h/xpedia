#include "itinerary.h"
#include "itineraryItem.h"
#include "reservation.h"
#include <iostream>
void Itinerary::add_item(Reservation *res)
{
    reservations.push_back(res);
}

void Itinerary::Clear()
{
    for (int i = 0; i < (int)reservations.size(); i++)
    {
        std::cout << "itinerary line 16\n";
        delete reservations[i];
        reservations[i] = nullptr;
    }
    reservations.clear();
}

std::string Itinerary::toString() const
{
    std::string str{};
    for (const auto &res : reservations)
    {
        str += res->toString();
    }
    return str;
}

std::string Itinerary::toString2() const
{
    std::string str{};
    for (const auto &res : reservations)
    {
        str += res->toString2();
    }
    return str;
}

double Itinerary::total_cost() const
{
    double cost{};
    for (auto &res : reservations)
    {
        cost += res->total_cost();
    }
    return cost;
}
