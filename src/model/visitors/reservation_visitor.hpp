#pragma once

class FlightReservation;
class HotelReservation;

class ReservationVisitor
{
public:
    virtual void visit(const FlightReservation &) = 0;

    virtual void visit(const HotelReservation &) = 0;

    virtual ~ReservationVisitor() = default;
};