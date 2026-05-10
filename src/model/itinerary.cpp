#include "itinerary.hpp"
#include "itinerary_item.hpp"
#include <iostream>

Itinerary::Itinerary(const Itinerary &other)
    : id(other.id), cost(other.cost)
{
    for (const auto &res : other.reservations)
        reservations.push_back(std::unique_ptr<Reservation>(res->Clone()));
}

Itinerary &Itinerary::operator=(const Itinerary &other)
{
    if (this == &other)
        return *this;
    id = other.id;
    cost = other.cost;
    reservations.clear();
    for (const auto &res : other.reservations)
        reservations.push_back(std::unique_ptr<Reservation>(res->Clone()));
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

std::vector<Reservation *> Itinerary::getReservations() const
{
    std::vector<Reservation *> result{};
    for (const auto &res : reservations)
        result.push_back(res.get());
    return result;
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
    for (const auto &res : reservations)
    {
        cost += res->total_cost();
    }
    return cost;
}
