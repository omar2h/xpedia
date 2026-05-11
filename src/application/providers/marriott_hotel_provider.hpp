#pragma once

#include "hotel_provider.hpp"

class MarriottHotelProvider : public HotelProvider
{
public:
    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    [[nodiscard]] bool reserve(Reservation *) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::unique_ptr<ReservationProvider> clone() const override;
};
