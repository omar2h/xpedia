#pragma once

#include <memory>

#include "../entities/reservation.hpp"

class ReservationFactory
{
  public:
    virtual ~ReservationFactory() = default;
    [[nodiscard]] virtual std::unique_ptr<Reservation> getReservation(RequestType);
};
