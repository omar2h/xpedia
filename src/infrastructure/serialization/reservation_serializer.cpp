#include "reservation_serializer.hpp"
#include "../json_keys.hpp"
#include "../../domain/request_type.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/hotel_reservation.hpp"

json ReservationSerializer::serialize(const Reservation &reservation)
{
    obj.clear();

    reservation.accept(*this);

    return obj;
}

json ReservationSerializer::toJson(const Reservation &reservation)
{
    obj.clear();

    reservation.accept(*this);

    obj[JsonKeys::type] = reservation.getType();
    obj[JsonKeys::requestType] = reservation.getRequestType();

    return obj;
}

void ReservationSerializer::visit(const FlightReservation &flight)
{
    obj[JsonKeys::airline] = flight.getAirline();

    obj[JsonKeys::from] = flight.getFrom();
    obj[JsonKeys::to] = flight.getTo();

    obj[JsonKeys::date] = flight.getDate();

    obj[JsonKeys::adults] = flight.getAdults();
    obj[JsonKeys::children] = flight.getChildren();

    obj[JsonKeys::cost] = flight.totalCost();
}

void ReservationSerializer::visit(const HotelReservation &hotel)
{
    obj[JsonKeys::hotel] = hotel.getHotelName();

    obj[JsonKeys::from] = hotel.getFromDate();
    obj[JsonKeys::to] = hotel.getToDate();

    obj[JsonKeys::city] = hotel.getCity();

    obj[JsonKeys::roomType] = hotel.getRoomType();

    obj[JsonKeys::rooms] = hotel.getRooms();

    obj[JsonKeys::adults] = hotel.getAdults();
    obj[JsonKeys::children] = hotel.getChildren();

    obj[JsonKeys::cost] = hotel.totalCost();
}

std::unique_ptr<Reservation> ReservationSerializer::fromJson(const json &obj)
{
    RequestType requestType = obj[JsonKeys::requestType].get<RequestType>();
    ReservationType resType = obj[JsonKeys::type].get<ReservationType>();

    if (requestType == RequestType::flight)
    {
        auto reservation = std::make_unique<FlightReservation>();
        reservation->setType(resType);
        reservation->setRequestType(requestType);
        reservation->setAirline(obj[JsonKeys::airline].get<std::string>());
        reservation->setFrom(obj[JsonKeys::from].get<std::string>());
        reservation->setTo(obj[JsonKeys::to].get<std::string>());
        reservation->setDate(obj[JsonKeys::date].get<std::string>());
        reservation->setAdults(obj[JsonKeys::adults].get<int>());
        reservation->setChildren(obj[JsonKeys::children].get<int>());
        reservation->setCost(obj[JsonKeys::cost].get<double>());
        return reservation;
    }

    auto reservation = std::make_unique<HotelReservation>();
    reservation->setType(resType);
    reservation->setRequestType(requestType);
    reservation->setHotelName(obj[JsonKeys::hotel].get<std::string>());
    reservation->setFromDate(obj[JsonKeys::from].get<std::string>());
    reservation->setToDate(obj[JsonKeys::to].get<std::string>());
    reservation->setCity(obj[JsonKeys::city].get<std::string>());
    reservation->setRoomType(obj[JsonKeys::roomType].get<std::string>());
    reservation->setAdults(obj[JsonKeys::adults].get<int>());
    reservation->setChildren(obj[JsonKeys::children].get<int>());
    reservation->setRooms(obj[JsonKeys::rooms].get<int>());
    reservation->setCost(obj[JsonKeys::cost].get<double>());
    return reservation;
}