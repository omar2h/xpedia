#include "hotel_reservation.hpp"
#include "../factories/reservation_request_factory.hpp"
#include "../dto/hotel_reservation_data.hpp"
#include "../visitors/reservation_visitor.hpp"

#include <sstream>
#include <string>

HotelReservation::HotelReservation(const HotelReservation &other)
    : item(nullptr),
      hotelName(other.hotelName),
      fromDate(other.fromDate),
      toDate(other.toDate),
      city(other.city),
      roomType(other.roomType),
      adults(other.adults),
      children(other.children),
      rooms(other.rooms),
      cost(other.cost)
{
    if (other.item)
    {
        item = std::unique_ptr<HotelRoom>(dynamic_cast<HotelRoom *>(other.item->clone().release()));
    }
    if (other.request)
    {
        request = std::make_unique<HotelRequest>(*other.request);
    }
}

HotelReservation::HotelReservation(const HotelReservationData &data)
{
    hotelName = data.hotelName;

    fromDate = data.fromDate;
    toDate = data.toDate;

    city = data.city;

    roomType = data.roomType;

    adults = data.adults;
    children = data.children;
    rooms = data.rooms;

    cost = data.cost;
}

HotelReservation &HotelReservation::operator=(
    const HotelReservation &other)
{
    if (this == &other)
        return *this;

    if (other.item)
    {
        item = std::unique_ptr<HotelRoom>(dynamic_cast<HotelRoom *>(other.item->clone().release()));
    }
    else
    {
        item.reset();
    }

    hotelName = other.hotelName;
    fromDate = other.fromDate;
    toDate = other.toDate;
    city = other.city;
    roomType = other.roomType;
    adults = other.adults;
    children = other.children;
    rooms = other.rooms;
    cost = other.cost;

    if (other.request)
    {
        request = std::make_unique<HotelRequest>(*other.request);
    }
    else
    {
        request.reset();
    }

    return *this;
}

std::unique_ptr<Reservation> HotelReservation::clone() const
{
    return std::make_unique<HotelReservation>(*this);
}

void HotelReservation::accept(ReservationVisitor &visitor) const
{
    visitor.visit(*this);
}

static int getNights(const std::string &from, const std::string &to)
{
    auto toInt = [](const std::string &s, size_t pos, size_t len) {
        return std::stoi(s.substr(pos, len));
    };
    int fromDays = toInt(from, 0, 4) * 365 + toInt(from, 5, 2) * 30 + toInt(from, 8, 2);
    int toDays = toInt(to, 0, 4) * 365 + toInt(to, 5, 2) * 30 + toInt(to, 8, 2);
    int nights = toDays - fromDays;
    return nights > 0 ? nights : 1;
}

double HotelReservation::totalCost() const
{
    return item->totalCost() * rooms * getNights(fromDate, toDate);
}

std::string HotelReservation::toString() const
{
    std::ostringstream oss;
    oss << "Hotel: " << item->getHotelName() << "," << request->getCity() << ", Room: "
        << item->getRoomType() << "(" << request->getRooms() << ") "
        << ", From: " << item->getDateFrom() << " to: " << item->getDateTo() << "\n";
    oss << "Adults: " << request->getAdults() << ", children: " << request->getChildren() << "\n";
    oss << "Total Cost:" << totalCost() << "\n";
    return oss.str();
}

std::string HotelReservation::toSummaryString() const
{
    std::ostringstream oss;
    oss << "Hotel: " << hotelName << "," << city << ", Room: " << roomType << "(" << rooms << ") "
        << ", From " << fromDate << " to " << toDate << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << cost << "\n";
    return oss.str();
}

void HotelReservation::setRequest(std::unique_ptr<ReservationRequest> req)
{
    request.reset(dynamic_cast<HotelRequest *>(req.release()));
    adults = request->getAdults();
    children = request->getChildren();
    rooms = request->getRooms();
    city = request->getCity();
}

void HotelReservation::setItem(const ItineraryItem &i)
{
    item.reset(dynamic_cast<HotelRoom *>(i.clone().release()));
    setType(&i);
    setRequestType(&i);
    hotelName = item->getHotelName();
    fromDate = item->getDateFrom();
    toDate = item->getDateTo();
    roomType = item->getRoomType();
}
