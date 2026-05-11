#pragma once

#include <string>
#include <memory>

#include "../../domain/entities/reservation.hpp"
#include "../../domain/visitors/reservation_visitor.hpp"
#include "../../third_party/json.hpp"
using json = nlohmann::json;

class ReservationSerializer : public ReservationVisitor
{
    json obj;

public:
    json toJson(const Reservation &);
    static std::unique_ptr<Reservation> fromJson(const json &);

    json serialize(const Reservation &);

    void visit(const FlightReservation &) override;

    void visit(const HotelReservation &) override;
};