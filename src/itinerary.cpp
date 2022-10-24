#include "itinerary.h"
#include "itineraryItem.h"
#include "reservation.h"
void Itinerary::add_item(Reservation *res)
{
    reservations.push_back(res);
}

void Itinerary::Clear()
{
    for (auto &res : reservations)
    {
        delete res;
        res = nullptr;
    }
    reservations.clear();
}

std::string Itinerary::toString()
{
    std::string str{};
    for (const auto &res : reservations)
    {
        str += res->toString();
    }
    return str;
}
