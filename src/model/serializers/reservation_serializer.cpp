#include "reservation_serializer.hpp"
#include "../requests/reservation_request.hpp"
#include "../reservations/flight_reservation.hpp"
#include "../reservations/hotel_reservation.hpp"
#include "../dto/flight_reservation_data.hpp"
#include "../dto/hotel_reservation_data.hpp"

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

    if (reqType == RequestType::flight)
    {
        FlightReservationData data;
        data.airline = obj["airline"];
        data.from = obj["from"];
        data.to = obj["to"];

        data.date = obj["date"];

        data.adults = obj["adults"];
        data.children = obj["children"];

        data.cost = obj["cost"];
        return std::make_unique<FlightReservation>(data);
    }

    HotelReservationData data;
    data.hotelName = obj["hotel"];

    data.fromDate = obj["from"];
    data.toDate = obj["to"];

    data.city = obj["city"];

    data.roomType = obj["room_type"];

    data.adults = obj["adults"];
    data.children = obj["children"];
    data.rooms = obj["rooms"];

    data.cost = obj["cost"];

    return std::make_unique<HotelReservation>(data);
}