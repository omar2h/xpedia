#pragma once

#include "../../model/requests/flight_request.hpp"
#include "../../model/reservations/flight_reservation.hpp"
#include "../../model/flight.hpp"
#include "reservation_provider.hpp"
#include <vector>

class FlightProvider : public ReservationProvider
{

public:
    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override = 0;

    [[nodiscard]] bool reserve(Reservation *) const override = 0;

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::unique_ptr<ReservationProvider> clone() const override = 0;

    ~FlightProvider() override = default;
};
