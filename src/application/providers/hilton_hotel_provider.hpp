#pragma once

#include "hotel_provider.hpp"

class HiltonHotelProvider : public HotelProvider
{
public:
    std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ReservationProvider *clone() override;

    ~HiltonHotelProvider() override = default;
};
