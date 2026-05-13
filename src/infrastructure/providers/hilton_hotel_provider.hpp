#pragma once

#include "../../application/providers/reservation_provider.hpp"

class HiltonHotelProvider : public ReservationProvider
{
public:
    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    [[nodiscard]] bool reserve(Reservation *) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getCategory() const override { return "hotel"; }
};
