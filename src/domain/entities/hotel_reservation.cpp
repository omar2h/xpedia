#include "hotel_reservation.hpp"
#include "../visitors/reservation_visitor.hpp"

#include <sstream>
#include <string>
#include <cassert>

HotelReservation::HotelReservation(const HotelReservation &other)
    : Reservation(other),
      item(other.item ? std::make_unique<HotelRoom>(*other.item) : nullptr),
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
}

HotelReservation &HotelReservation::operator=(
    const HotelReservation &other)
{
    if (this == &other)
        return *this;

    Reservation::operator=(other);

    if (other.item)
    {
        item = std::make_unique<HotelRoom>(*other.item);
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
    auto toInt = [](const std::string &s, size_t pos, size_t len)
    {
        return std::stoi(s.substr(pos, len));
    };
    int fromDays = toInt(from, 0, 4) * 365 + toInt(from, 5, 2) * 30 + toInt(from, 8, 2);
    int toDays = toInt(to, 0, 4) * 365 + toInt(to, 5, 2) * 30 + toInt(to, 8, 2);
    int nights = toDays - fromDays;
    return nights > 0 ? nights : 1;
}

double HotelReservation::totalCost() const
{
    if (item)
    {
        return item->totalCost() * rooms * getNights(fromDate, toDate);
    }
    return cost;
}

std::string HotelReservation::toString() const
{
    std::ostringstream oss;
    oss << "Hotel: " << hotelName << "," << city << ", Room: " << roomType << "(" << rooms << ") "
        << ", From: " << fromDate << " to: " << toDate << "\n";
    oss << "Adults: " << adults << ", children: " << children << "\n";
    oss << "Total Cost:" << totalCost() << "\n";
    return oss.str();
}

std::string HotelReservation::toSummaryString() const
{
    std::ostringstream oss;
    oss << "Hotel: " << hotelName << "," << city << ", Room: " << roomType << "(" << rooms << ") "
        << ", From " << fromDate << " to " << toDate << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << totalCost() << "\n";
    return oss.str();
}

void HotelReservation::setItem(const ItineraryItem &i)
{
    assert(dynamic_cast<const HotelRoom *>(&i) != nullptr && "Item must be a HotelRoom");
    item = std::make_unique<HotelRoom>(static_cast<const HotelRoom &>(i));
    setType(&i);
    setRequestType(&i);
    hotelName = item->getHotelName();
    fromDate = item->getDateFrom();
    toDate = item->getDateTo();
    roomType = item->getRoomType();
}
