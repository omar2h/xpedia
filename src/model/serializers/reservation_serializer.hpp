#pragma once

#include <string>
#include <memory>

#include "../reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../../third_party/json.hpp"
using json = nlohmann::json;

class ReservationSerializer : public ReservationVisitor
{
    json obj;

public:
    json to_json(const Reservation &);
    static std::unique_ptr<Reservation> from_json(const json &);

    json serialize(const Reservation &);

    void visit(const FlightReservation &) override;

    void visit(const HotelReservation &) override;
};