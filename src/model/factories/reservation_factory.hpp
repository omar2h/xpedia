#pragma once

#include "../reservation.hpp"
enum class RequestType;

class ReservationFactory
{
public:
    static Reservation *getReservation(RequestType);
};
