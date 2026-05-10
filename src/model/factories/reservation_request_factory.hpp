#pragma once

#include <memory>

#include "../requests/reservation_request.hpp"

class ReservationRequestFactory
{
public:
    static std::unique_ptr<ReservationRequest> getRequest(RequestType);
};
