#include "itinerary.hpp"
#include "itinerary_item.hpp"
#include <iostream>

Itinerary::Itinerary(const Itinerary &other)
    : id(other.id), cost(other.cost)
{
    for (const auto &res : other.reservations)
        reservations.push_back(res->clone());
}

Itinerary &Itinerary::operator=(const Itinerary &other)
{
    if (this == &other)
        return *this;
    id = other.id;
    cost = other.cost;
    reservations.clear();
    for (const auto &res : other.reservations)
        reservations.push_back(res->clone());
    return *this;
}

void Itinerary::add_item(std::unique_ptr<Reservation> res)
{
    reservations.push_back(std::move(res));
}

void Itinerary::Clear()
{
    reservations.clear();
}

const std::vector<std::unique_ptr<Reservation>> &
Itinerary::getReservations() const
{
    return reservations;
}

void Itinerary::setReservations(std::vector<std::unique_ptr<Reservation>> reservations_)
{
    reservations = std::move(reservations_);
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

std::string Itinerary::toSummaryString() const
{
    std::string str{};
    for (const auto &res : reservations)
    {
        str += res->toSummaryString();
    }
    return str;
}

double Itinerary::total_cost() const
{
    double cost{};
    for (const auto &res : reservations)
    {
        cost += res->total_cost();
    }
    return cost;
}
