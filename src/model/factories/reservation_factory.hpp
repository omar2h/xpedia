#pragma once

#include <memory>

#include "../reservation.hpp"
enum class RequestType;

class ReservationFactory
{
public:
    static std::unique_ptr<Reservation> getReservation(RequestType);
};
