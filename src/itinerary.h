#ifndef __ITINERARY_H__
#define __ITINERARY_H__
#include <vector>
#include <string>
class Reservation;

class Itinerary
{
    std::string id{};
    std::vector<Reservation *> reservations{};

public:
    Itinerary(std::string id) : id{id} {}
    std::string getId() const { return id; }
    void add_item(Reservation *);
    void Clear();
    std::string toString();
    double total_cost() const;
    std::vector<Reservation *> getReservations() const { return reservations; }
    void setReservations(const std::vector<Reservation *> &reservations_) { reservations = reservations_; }
};
#endif // __ITINERARY_H__