#include "flight_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../requests/flight_request.hpp"
#include "../../exception.hpp"

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
    return cost;
}

void FlightReservation::setItem(const ItineraryItem &i)
{
    auto *f = dynamic_cast<const Flight *>(&i);
    if (!f)
        throw BusinessException("FlightReservation::setItem expected Flight");
    flight = *f;
    hasFlight = true;
    setCategory(&i);
    copyProviderFrom(&i);
    setRequestType(&i);
}

void FlightReservation::recalculateCost()
{
    if (!hasFlight)
        throw BusinessException("FlightReservation: flight not set");
    if (adults == 0 && children == 0)
        throw BusinessException("FlightReservation: no passengers");
    cost = flight.getTotalCost() * adults + flight.getTotalCost() * children * 0.5;
}

void FlightReservation::applyRequest(const ReservationRequest &req)
{
    auto *flightReq = dynamic_cast<const FlightRequest *>(&req);
    if (!flightReq)
        throw BusinessException("FlightReservation::applyRequest expected FlightRequest");
    from = flightReq->getFromCity();
    to = flightReq->getToCity();
    adults = flightReq->getAdults();
    children = flightReq->getChildren();
    recalculateCost();
}
