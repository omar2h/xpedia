#ifndef __ITINERARY_H__
#define __ITINERARY_H__
#include <vector>
#include <string>
class Reservation;

class Itinerary
{
    std::string id{};
    double cost{};
    std::vector<Reservation *> reservations{};

public:
    std::string getId() const { return id; }
    void setId(std::string id_) { id = id_; }
    void add_item(Reservation *);
    void Clear();
    std::string toString() const;
    std::string toString2() const;
    double total_cost() const;
    std::vector<Reservation *> getReservations() const { return reservations; }
    void setReservations(const std::vector<Reservation *> &reservations_) { reservations = reservations_; }

    double getCost() const { return cost; }
    void setCost() { cost = total_cost(); }
    void setCost(double cost_) { cost = cost_; }
};
#endif // __ITINERARY_H__