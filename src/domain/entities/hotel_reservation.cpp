#include "hotel_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../requests/hotel_request.hpp"
#include "../../exception.hpp"

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

static void parseDate(const std::string &s, std::tm &tm)
{
    std::istringstream ss(s);
    if (s.size() >= 10 && s[4] == '-')
        ss >> std::get_time(&tm, "%Y-%m-%d");
    else
        ss >> std::get_time(&tm, "%d-%m-%Y");
    if (ss.fail())
        throw BusinessException("Invalid hotel reservation dates");
}

static int getNights(const std::string &from, const std::string &to)
{
    std::tm fromTm = {};
    std::tm toTm = {};
    parseDate(from, fromTm);
    parseDate(to, toTm);
    fromTm.tm_isdst = -1;
    toTm.tm_isdst = -1;

    auto fromTime = std::mktime(&fromTm);
    auto toTime = std::mktime(&toTm);
    if (fromTime == -1 || toTime == -1)
        throw BusinessException("Invalid hotel reservation dates");

    double diff = std::difftime(toTime, fromTime);
    int nights = static_cast<int>(diff / (60 * 60 * 24));
    if (nights <= 0)
        throw BusinessException("Invalid hotel reservation dates");
    return nights;
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
    return cost;
}

void HotelReservation::setItem(const ItineraryItem &i)
{
    auto *r = dynamic_cast<const HotelRoom *>(&i);
    if (!r)
        throw BusinessException("HotelReservation::setItem expected HotelRoom");
    room = *r;
    hasRoom = true;
    setCategory(&i);
    copyProviderFrom(&i);
    setRequestType(&i);
}

void HotelReservation::recalculateCost()
{
    if (!hasRoom)
        throw BusinessException("HotelReservation: room not set");
    if (rooms == 0)
        throw BusinessException("HotelReservation: no rooms requested");
    cost = room.totalCost() * rooms * getNights(room.getDateFrom(), room.getDateTo());
}

void HotelReservation::applyRequest(const ReservationRequest &req)
{
    auto *hotelReq = dynamic_cast<const HotelRequest *>(&req);
    if (!hotelReq)
        throw BusinessException("HotelReservation::applyRequest expected HotelRequest");
    city = hotelReq->getCity();
    rooms = hotelReq->getRooms();
    adults = hotelReq->getAdults();
    children = hotelReq->getChildren();
    recalculateCost();
}
