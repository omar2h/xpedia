#pragma once

#include <memory>
#include <string>

#include "../request_type.hpp"

class ReservationRequest
{
public:
    [[nodiscard]] virtual std::unique_ptr<ReservationRequest> clone() = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    virtual ~ReservationRequest() = 0;
};

inline ReservationRequest::~ReservationRequest() = default;
