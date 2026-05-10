#pragma once

#include <string>
#include <memory>

#include "../reservation.hpp"
#include "../../include/json.hpp"
using json = nlohmann::json;

class ReservationSerializer
{
public:
    static json to_json(const Reservation &);

    static std::unique_ptr<Reservation> from_json(const json &);
};