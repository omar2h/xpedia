#include "flight_reservation.hpp"
#include "../factories/reservation_request_factory.hpp"
#include "../dto/flight_reservation_data.hpp"
#include <sstream>
#include <iostream>

FlightReservation::FlightReservation(const FlightReservation &other)
    : airline(other.airline),
      from(other.from),
      to(other.to),
      date(other.date),
      adults(other.adults),
      children(other.children),
      cost(other.cost),
      item(nullptr)
{
    if (other.item)
    {
        item = std::unique_ptr<Flight>(dynamic_cast<Flight *>(other.item->clone().release()));
    }
    if (other.request)
    {
        request = std::make_unique<FlightRequest>(*other.request);
    }
}

FlightReservation::FlightReservation(
    const FlightReservationData &data)
{
    airline = data.airline;

    from = data.from;
    to = data.to;

    date = data.date;

    adults = data.adults;
    children = data.children;

    cost = data.cost;
}

FlightReservation &FlightReservation::operator=(const FlightReservation &other)
{
    if (this == &other)
        return *this;

    airline = other.airline;
    from = other.from;
    to = other.to;
    date = other.date;
    adults = other.adults;
    children = other.children;
    cost = other.cost;

    if (other.item)
    {
        item = std::unique_ptr<Flight>(dynamic_cast<Flight *>(other.item->clone().release()));
    }
    else
    {
        item.reset();
    }

    if (other.request)
    {
        request = std::make_unique<FlightRequest>(*other.request);
    }
    else
    {
        request.reset();
    }

    return *this;
}

std::unique_ptr<Reservation> FlightReservation::clone() const
{
    return std::make_unique<FlightReservation>(*this);
}

double FlightReservation::total_cost() const
{
    return item->getTotalCost() * request->getAdults() +
           item->getTotalCost() * request->getChildren() * 0.5;
}

std::string FlightReservation::toString() const
{
    std::ostringstream oss;
    oss << "Airline: " << item->getAirline() << ": From " << request->getFromCity() << " to " << request->getToCity() << " on " << item->getDate() << "\n";
    oss << "Adults: " << request->getAdults() << ", children: " << request->getChildren() << "\n";
    oss << "Total Cost:" << total_cost() << "\n";
    return oss.str();
}

std::string FlightReservation::toString2() const
{
    std::ostringstream oss;
    oss << "Airline: " << airline << ", From " << from << " to " << to << " on " << date << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << cost << "\n";
    return oss.str();
}

void FlightReservation::setRequest(std::unique_ptr<ReservationRequest> request)
{
    this->request.reset(dynamic_cast<FlightRequest *>(request.release()));
}

void FlightReservation::setItem(ItineraryItem *const i)
{
    item = std::unique_ptr<Flight>(dynamic_cast<Flight *>(i->clone().release()));
    setType(i);
    setReqType(i);
}
