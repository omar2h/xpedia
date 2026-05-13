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
    [[nodiscard]] json toJson(const Reservation &);
    [[nodiscard]] static std::unique_ptr<Reservation> fromJson(const json &);

    [[nodiscard]] json serialize(const Reservation &);

    void visit(const FlightReservation &) override;

    void visit(const HotelReservation &) override;
};