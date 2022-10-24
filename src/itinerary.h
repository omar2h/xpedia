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
    double total_cost() const;
    std::vector<Reservation *> getReservations() const { return reservations; }
    void setReservations(const std::vector<Reservation *> &reservations_) { reservations = reservations_; }
};
#endif // __ITINERARY_H__