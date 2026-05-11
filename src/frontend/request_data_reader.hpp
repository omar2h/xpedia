#pragma once

#include "../model/requests/reservation_request.hpp"

class RequestDataReader
{
public:
    [[nodiscard]] virtual ReservationRequest *read() = 0;
    virtual ~RequestDataReader() = 0;
};
