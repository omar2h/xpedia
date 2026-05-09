#pragma once

#include "../model/requests/reservation_request.hpp"

class RequestDataReader
{
public:
    virtual ReservationRequest *read() = 0;
    virtual ~RequestDataReader() = 0;
};
