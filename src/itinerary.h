#ifndef __ITINERARY_H__
#define __ITINERARY_H__
#include <vector>
#include <string>
class Reservation;

class Itinerary
{
    std::vector<Reservation *> reservations{};

public:
    void add_item(Reservation *);
    void Clear();
    std::string toString();
};
#endif // __ITINERARY_H__