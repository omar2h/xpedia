#pragma once

#include "../requests/reservation_request.hpp"

class ReservationRequestFactory
{
public:
    static ReservationRequest *getRequest(RequestType);
};
