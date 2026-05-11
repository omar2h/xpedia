#pragma once

#include "../../model/requests/hotel_request.hpp"
#include "../../model/reservations/hotel_reservation.hpp"
#include "reservation_provider.hpp"
#include <vector>
class HotelProvider : public ReservationProvider
{
public:
    std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override = 0;

    bool reserve(Reservation *) const override = 0;

    std::string getName() const override = 0;

    std::unique_ptr<ReservationProvider> clone() const override = 0;

    ~HotelProvider() override = default;
};
