#include "flight_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../../application/requests/flight_request.hpp"

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
    if (hasFlight)
        return flight.getTotalCost() * adults + flight.getTotalCost() * children * 0.5;
    return cost;
}

void FlightReservation::setItem(const ItineraryItem &i)
{
    auto &f = dynamic_cast<const Flight &>(i);
    flight = f;
    hasFlight = true;
    setCategory(&i);
    copyProviderFrom(&i);
    setRequestType(&i);
}

void FlightReservation::applyRequest(const ReservationRequest &req)
{
    auto &flightReq = dynamic_cast<const FlightRequest &>(req);
    from = flightReq.getFromCity();
    to = flightReq.getToCity();
    adults = flightReq.getAdults();
    children = flightReq.getChildren();
}
