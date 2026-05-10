#pragma once

#include "../reservation.hpp"
#include "../flight.hpp"
#include "../requests/flight_request.hpp"
#include <memory>
using json = nlohmann::json;

class FlightReservation : public Reservation
{
    FlightRequest *request{};
    Flight *item{};
    std::string airline{};
    std::string from{};
    std::string to{};
    std::string date{};
    int adults{};
    int children{};
    double cost{};

public:
    Reservation *Clone() const override { return new FlightReservation(*this); }

    double total_cost() const override;

    std::string toString() const override;

    std::string toString2() const override;

    void setRequest(ReservationRequest *const) override;

    void setItem(ItineraryItem *const) override;

    json toJson() const override;

    std::unique_ptr<Reservation> jsonToReservation(json) override;

    void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) override;

    ~FlightReservation() override;
};
