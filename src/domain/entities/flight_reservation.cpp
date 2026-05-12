#include "flight_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include <sstream>
#include <cassert>

FlightReservation::FlightReservation(const FlightReservation &other)
    : Reservation(other),
      airline(other.airline),
      from(other.from),
      to(other.to),
      date(other.date),
      adults(other.adults),
      children(other.children),
      cost(other.cost),
      item(other.item ? std::make_unique<Flight>(*other.item) : nullptr)
{
}

FlightReservation &FlightReservation::operator=(const FlightReservation &other)
{
    if (this == &other)
        return *this;

    Reservation::operator=(other);

    airline = other.airline;
    from = other.from;
    to = other.to;
    date = other.date;
    adults = other.adults;
    children = other.children;
    cost = other.cost;

    if (other.item)
    {
        item = std::make_unique<Flight>(*other.item);
    }
    else
    {
        item.reset();
    }

    return *this;
}

std::unique_ptr<Reservation> FlightReservation::clone() const
{
    return std::make_unique<FlightReservation>(*this);
}

void FlightReservation::accept(ReservationVisitor &visitor) const
{
    visitor.visit(*this);
}

double FlightReservation::totalCost() const
{
    if (item)
    {
        return item->getTotalCost() * adults +
               item->getTotalCost() * children * 0.5;
    }
    return cost;
}

void FlightReservation::setItem(const ItineraryItem &i)
{
    assert(dynamic_cast<const Flight *>(&i) != nullptr && "Item must be a Flight");
    item = std::make_unique<Flight>(static_cast<const Flight &>(i));
    setCategory(&i);
    copyProviderFrom(&i);
    setRequestType(&i);
    airline = item->getAirline();
    date = item->getDate();
}
