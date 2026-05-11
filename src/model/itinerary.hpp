#pragma once

#include <vector>
#include <string>
#include <memory>

#include "reservation.hpp"

class Itinerary
{
    std::string id{};
    double cost{};
    std::vector<std::unique_ptr<Reservation>> reservations{};

public:
    Itinerary() = default;
    Itinerary(const Itinerary &);
    Itinerary &operator=(const Itinerary &);
    Itinerary(Itinerary &&) noexcept = default;
    Itinerary &operator=(Itinerary &&) noexcept = default;

    std::string getId() const { return id; }
    void setId(std::string id_) { id = id_; }
    void addItem(std::unique_ptr<Reservation>);
    void clear();
    std::string toString() const;
    std::string toSummaryString() const;
    double total_cost() const;
    const std::vector<std::unique_ptr<Reservation>> &getReservations() const;
    void setReservations(std::vector<std::unique_ptr<Reservation>> reservations_);

    double getCost() const { return cost; }
    void setCost() { cost = total_cost(); }
    void setCost(double cost_) { cost = cost_; }
};
