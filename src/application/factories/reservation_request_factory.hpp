#pragma once

#include <memory>

#include "../requests/reservation_request.hpp"

class ReservationRequestFactory
{
public:
    virtual ~ReservationRequestFactory() = default;
    [[nodiscard]] virtual std::unique_ptr<ReservationRequest> getRequest(RequestType);
};
