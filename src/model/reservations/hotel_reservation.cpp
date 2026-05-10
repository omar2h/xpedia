#include "hotel_reservation.hpp"
#include "../factories/reservation_request_factory.hpp"
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

json HotelReservation::toJson() const
{
    json obj;
    obj["hotel"] = item->getHotelName();
    obj["from"] = request->getFromDate();
    obj["to"] = request->getToDate();
    obj["city"] = request->getCity();
    obj["adults"] = request->getAdults();
    obj["children"] = request->getChildren();
    obj["room_type"] = item->getRoomType();
    obj["rooms"] = request->getRooms();
    obj["type"] = getType();
    obj["reqType"] = getReqType();
    obj["cost"] = total_cost();
    return obj;
}

std::unique_ptr<Reservation> HotelReservation::jsonToReservation(json obj)
{
    std::string hotel = obj.value("hotel", "not found");
    std::string from = obj.value("from", "not found");
    std::string to = obj.value("to", "not found");
    std::string city = obj.value("city", "not found");
    std::string roomType = obj.value("room_type", "not found");
    int rooms = obj.value("rooms", -1);
    int adults = obj.value("adults", -1);
    int children = obj.value("children", -1);
    double cost = obj.value("cost", -1);

    setAttributes(hotel, from, to, city, adults, children, cost, roomType, rooms);
    return std::unique_ptr<Reservation>(this->clone());
}

void HotelReservation::setAttributes(const std::string &hotel, const std::string &from_, const std::string &to_, const std::string &city_, int adults_, int children_, double cost_, const std::string &roomType_, int rooms_)
{
    hotelName = hotel;
    fromDate = from_;
    toDate = to_;
    city = city_;
    adults = adults_;
    children = children_;
    cost = cost_;
    roomType = roomType_;
    rooms = rooms_;
}
