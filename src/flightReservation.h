#ifndef __FLIGHTRESERVATION_H__
#define __FLIGHTRESERVATION_H__
#include "reservation.h"
#include "flight.h"
#include "flightRequest.h"
using json = nlohmann::json;

class FlightReservation : public Reservation
{
    FlightRequest *request{};
    Flight *item{};

public:
    Reservation *Clone() const override { return new FlightReservation(*this); }

    double total_cost() const override;

    std::string toString() const override;

    void setRequest(ReservationRequest *const) override;

    void setItem(ItineraryItem *const) override;

    json toJson() const override;

    virtual ~FlightReservation() = default;
};
#endif // __FLIGHTRESERVATION_H__