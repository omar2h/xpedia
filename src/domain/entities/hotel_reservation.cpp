#include "hotel_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../requests/hotel_request.hpp"

#include <string>

static int getNights(const std::string &from, const std::string &to)
{
    auto toInt = [](const std::string &s, size_t pos, size_t len)
    {
        return std::stoi(s.substr(pos, len));
    };
    int fromDays = toInt(from, 0, 4) * 365 + toInt(from, 5, 2) * 30 + toInt(from, 8, 2);
    int toDays = toInt(to, 0, 4) * 365 + toInt(to, 5, 2) * 30 + toInt(to, 8, 2);
    int nights = toDays - fromDays;
    return nights > 0 ? nights : 1;
}

std::unique_ptr<Reservation> HotelReservation::clone() const
{
    return std::make_unique<HotelReservation>(*this);
}

void HotelReservation::accept(ReservationVisitor &visitor) const
{
    visitor.visit(*this);
}

double HotelReservation::totalCost() const
{
    if (hasRoom)
        return room.totalCost() * rooms * getNights(room.getDateFrom(), room.getDateTo());
    return cost;
}

void HotelReservation::setItem(const ItineraryItem &i)
{
    auto &r = dynamic_cast<const HotelRoom &>(i);
    room = r;
    hasRoom = true;
    setCategory(&i);
    copyProviderFrom(&i);
    setRequestType(&i);
}

void HotelReservation::applyRequest(const ReservationRequest &req)
{
    auto &hotelReq = dynamic_cast<const HotelRequest &>(req);
    city = hotelReq.getCity();
    rooms = hotelReq.getRooms();
    adults = hotelReq.getAdults();
    children = hotelReq.getChildren();
}
