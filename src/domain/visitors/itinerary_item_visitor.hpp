#pragma once

// Forward declarations
class Flight;
class HotelRoom;

class ItineraryItemVisitor
{
public:
    virtual void visit(const Flight &item) = 0;
    virtual void visit(const HotelRoom &item) = 0;
    virtual ~ItineraryItemVisitor() = default;
};
