#include "flight_reservation.hpp"

#include "../visitors/reservation_visitor.hpp"

#include "../../exception.hpp"

std::unique_ptr<Reservation>
FlightReservation::clone() const
{
    return std::make_unique<FlightReservation>(*this);
}

void FlightReservation::accept(
    ReservationVisitor &visitor) const
{
    visitor.visit(*this);
}

double FlightReservation::totalCost() const
{
    return cost;
}

void FlightReservation::setItem(const ItineraryItem &item)
{
    auto *flight =
        dynamic_cast<const Flight *>(&item);

    if (!flight)
    {
        throw BusinessException(
            "FlightReservation::setItem expected Flight");
    }

    this->flight = *flight;

    hasFlight = true;

    setCategory(item.getCategory());

    setProviderId(item.getProviderId());

    setRequestType(item.getRequestType());
}

void FlightReservation::recalculateCost()
{
    if (!hasFlight)
    {
        throw BusinessException(
            "FlightReservation: flight not set");
    }

    if (adults == 0 && children == 0)
    {
        throw BusinessException(
            "FlightReservation: no passengers");
    }

    cost =
        flight.getTotalCost() * adults +
        flight.getTotalCost() * children * 0.5;
}

void FlightReservation::applySearchRequest(
    const FlightSearchRequest &request)
{
    from = request.origin;

    to = request.destination;

    adults = request.adults;

    children = request.children;

    recalculateCost();
}
