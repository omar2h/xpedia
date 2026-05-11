#pragma once

#include <memory>

#include "../../domain/entities/reservation.hpp"
enum class RequestType;

class ReservationFactory
{
public:
    virtual ~ReservationFactory() = default;
    [[nodiscard]] virtual std::unique_ptr<Reservation> getReservation(RequestType);
};
