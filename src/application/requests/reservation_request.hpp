#pragma once

#include <memory>
#include <string>

enum class RequestType
{
    flight,
    hotel
};

class ReservationRequest
{
public:
    [[nodiscard]] virtual std::unique_ptr<ReservationRequest> clone() = 0;
    virtual std::string toString() const = 0;
    virtual ~ReservationRequest() = 0;
};

inline ReservationRequest::~ReservationRequest() = default;
