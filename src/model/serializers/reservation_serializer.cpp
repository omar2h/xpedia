#include "reservation_serializer.hpp"
#include "../factories/reservation_factory.hpp"
#include "../requests/reservation_request.hpp"
#include "../reservations/flight_reservation.hpp"
#include "../reservations/hotel_reservation.hpp"

json ReservationSerializer::to_json(const Reservation &reservation)
{
    json obj;

    if (reservation.getReqType() == RequestType::flight)
    {
        const auto &flight = dynamic_cast<const FlightReservation &>(reservation);

        obj["airline"] = flight.getAirline();
        obj["from"] = flight.getFrom();
        obj["to"] = flight.getTo();
        obj["date"] = flight.getDate();
        obj["adults"] = flight.getAdults();
        obj["children"] = flight.getChildren();
        obj["cost"] = flight.total_cost();
    }
    else if (reservation.getReqType() == RequestType::hotel)
    {
        const auto &hotel = dynamic_cast<const HotelReservation &>(reservation);

        obj["hotel"] = hotel.getHotelName();
        obj["from"] = hotel.getFromDate();
        obj["to"] = hotel.getToDate();
        obj["city"] = hotel.getCity();
        obj["room_type"] = hotel.getRoomType();
        obj["rooms"] = hotel.getRooms();
        obj["adults"] = hotel.getAdults();
        obj["children"] = hotel.getChildren();
        obj["cost"] = hotel.total_cost();
    }

    obj["type"] = reservation.getType();
    obj["reqType"] = reservation.getReqType();

    return obj;
}

std::unique_ptr<Reservation> ReservationSerializer::from_json(const json &obj)
{
    RequestType reqType = obj["reqType"].get<RequestType>();

    auto reservation = ReservationFactory::getReservation(reqType);

    if (reqType == RequestType::flight)
    {
        reservation->setAttributes(
            obj["airline"],
            obj["from"],
            obj["to"],
            obj["date"],
            obj["adults"],
            obj["children"],
            obj["cost"]);
    }
    else if (reqType == RequestType::hotel)
    {
        reservation->setAttributes(
            obj["hotel"],
            obj["from"],
            obj["to"],
            obj["city"],
            obj["adults"],
            obj["children"],
            obj["cost"],
            obj["room_type"],
            obj["rooms"]);
    }

    return reservation;
}