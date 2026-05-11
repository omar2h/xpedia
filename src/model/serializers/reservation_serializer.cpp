#include "reservation_serializer.hpp"
#include "../requests/reservation_request.hpp"
#include "../reservations/flight_reservation.hpp"
#include "../reservations/hotel_reservation.hpp"
#include "../dto/flight_reservation_data.hpp"
#include "../dto/hotel_reservation_data.hpp"

json ReservationSerializer::serialize(const Reservation &reservation)
{
    obj.clear();

    reservation.accept(*this);

    return obj;
}

json ReservationSerializer::to_json(const Reservation &reservation)
{
    obj.clear();

    reservation.accept(*this);

    obj["type"] = reservation.getType();
    obj["requestType"] = reservation.getRequestType();

    return obj;
}

void ReservationSerializer::visit(const FlightReservation &flight)
{
    obj["airline"] = flight.getAirline();

    obj["from"] = flight.getFrom();
    obj["to"] = flight.getTo();

    obj["date"] = flight.getDate();

    obj["adults"] = flight.getAdults();
    obj["children"] = flight.getChildren();

    obj["cost"] = flight.total_cost();
}

void ReservationSerializer::visit(const HotelReservation &hotel)
{
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

std::unique_ptr<Reservation> ReservationSerializer::from_json(const json &obj)
{
    RequestType requestType = obj["requestType"].get<RequestType>();

    if (requestType == RequestType::flight)
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