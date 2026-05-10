#pragma once

#include <string>

enum class RequestType
{
    flight,
    hotel
};

class ReservationRequest
{
public:
    virtual ReservationRequest *clone() = 0;
    virtual std::string toString() const = 0;
    virtual ~ReservationRequest() = 0;
};

inline ReservationRequest::~ReservationRequest() = default;
