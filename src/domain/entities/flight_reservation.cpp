#include "flight_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include <sstream>

FlightReservation::FlightReservation(const FlightReservation &other)
    : Reservation(other),
      airline(other.airline),
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
        item = std::unique_ptr<Flight>(dynamic_cast<Flight *>(other.item->clone().release()));
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

std::string FlightReservation::toString() const
{
    std::ostringstream oss;
    oss << "Airline: " << airline << ": From " << from << " to " << to << " on " << date << "\n";
    oss << "Adults: " << adults << ", children: " << children << "\n";
    oss << "Total Cost:" << totalCost() << "\n";
    return oss.str();
}

std::string FlightReservation::toSummaryString() const
{
    std::ostringstream oss;
    oss << "Airline: " << airline << ", From " << from << " to " << to << " on " << date << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << totalCost() << "\n";
    return oss.str();
}

void FlightReservation::setItem(const ItineraryItem &i)
{
    item = std::unique_ptr<Flight>(dynamic_cast<Flight *>(i.clone().release()));
    setType(&i);
    setRequestType(&i);
    airline = item->getAirline();
    date = item->getDate();
}
