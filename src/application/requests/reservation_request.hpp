#pragma once

#include <memory>
#include <string>

#include "../../domain/request_type.hpp"

class ReservationRequest
{
public:
    [[nodiscard]] virtual std::unique_ptr<ReservationRequest> clone() = 0;
    virtual std::string toString() const = 0;
    virtual ~ReservationRequest() = 0;
};

inline ReservationRequest::~ReservationRequest() = default;
