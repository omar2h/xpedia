#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../../domain/entities/flight.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/hotel_reservation.hpp"
#include "../../domain/entities/hotel_room.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/itinerary_item.hpp"
#include "../../domain/entities/payment_card.hpp"
#include "../../domain/entities/reservation.hpp"
#include "../../domain/visitors/itinerary_item_visitor.hpp"
#include "../../domain/visitors/reservation_visitor.hpp"

class FormattingVisitor : public ReservationVisitor, public ItineraryItemVisitor
{
  public:
    std::string result;

    void visit(const Flight& f) override
    {
        std::ostringstream oss;
        oss << "Airline: " << f.getAirline() << ", Cost: " << f.getTotalCost() << ", Date: " << f.getDate();
        result = oss.str();
    }

    void visit(const HotelRoom& h) override
    {
        std::ostringstream oss;
        oss << "Hotel: " << h.getHotelName() << ", " << h.getRoomType() << " (" << h.getAvailableRooms()
            << " available), "
            << "Price/night: " << h.getPricePerNight() << ", From: " << h.getDateFrom() << " To: " << h.getDateTo();
        result = oss.str();
    }

    void visit(const FlightReservation& fr) override
    {
        std::ostringstream oss;
        oss << "Flight: " << fr.getAirline() << ", From " << fr.getFrom() << " to " << fr.getTo() << " on "
            << fr.getDate() << ", Adults: " << fr.getAdults() << ", Children: " << fr.getChildren()
            << ", Total Cost: " << fr.totalCost() << "\n";
        result = oss.str();
    }

    void visit(const HotelReservation& hr) override
    {
        std::ostringstream oss;
        oss << "Hotel: " << hr.getHotelName() << ", " << hr.getCity() << ", Room: " << hr.getRoomType() << " ("
            << hr.getRooms() << " rooms), From " << hr.getFromDate() << " to " << hr.getToDate()
            << ", Adults: " << hr.getAdults() << ", Children: " << hr.getChildren()
            << ", Total Cost: " << hr.totalCost() << "\n";
        result = oss.str();
    }
};

inline std::string formatItineraryItem(const ItineraryItem& item)
{
    FormattingVisitor visitor;
    item.accept(visitor);
    return visitor.result;
}

inline std::string formatReservationSummary(const Reservation& res)
{
    FormattingVisitor visitor;
    res.accept(visitor);
    return visitor.result;
}

inline std::string formatItinerarySummary(const Itinerary& itinerary)
{
    std::ostringstream oss;
    const auto& reservations = itinerary.getReservations();
    int count = static_cast<int>(reservations.size());
    oss << "Itinerary of " << count << " reservations\n";
    for (const auto& resPtr : reservations)
    {
        oss << formatReservationSummary(*resPtr);
    }
    return oss.str();
}

inline std::string formatPaymentCard(const PaymentCard& card)
{
    std::ostringstream oss;
    auto num = card.getNumber();
    std::string masked = num.size() > 4 ? "****-****-****-" + num.substr(num.size() - 4) : num;
    oss << "Card: " << masked << ", Owner: " << card.getOwner() << ", Expiry: " << card.getExpiryDate();
    return oss.str();
}
