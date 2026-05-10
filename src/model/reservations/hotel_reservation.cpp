#include "hotel_reservation.hpp"
#include "../factories/reservation_request_factory.hpp"
#include "../dto/hotel_reservation_data.hpp"
#include "../visitors/reservation_visitor.hpp"

#include <sstream>

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

double HotelReservation::total_cost() const
{
    return item->total_cost() * request->getRooms();
}

std::string HotelReservation::toString() const
{
    std::ostringstream oss;
    oss << "Hotel: " << item->getHotelName() << "," << request->getCity() << ", Room: "
        << item->getRoomType() << "(" << request->getRooms() << ") "
        << ", From: " << item->getDateFrom() << " to: " << item->getDateTo() << "\n";
    oss << "Adults: " << request->getAdults() << ", children: " << request->getChildren() << "\n";
    oss << "Total Cost:" << total_cost() << "\n";
    return oss.str();
}

std::string HotelReservation::toString2() const
{
    std::ostringstream oss;
    oss << "Hotel: " << hotelName << "," << city << ", Room: " << roomType << "(" << rooms << ") "
        << ", From " << fromDate << " to " << toDate << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << cost << "\n";
    return oss.str();
}

void HotelReservation::setRequest(std::unique_ptr<ReservationRequest> request)
{
    this->request.reset(dynamic_cast<HotelRequest *>(request.release()));
}

void HotelReservation::setItem(ItineraryItem *const i)
{
    item.reset(dynamic_cast<HotelRoom *>(i->clone().release()));
    setType(i);
    setReqType(i);
}
