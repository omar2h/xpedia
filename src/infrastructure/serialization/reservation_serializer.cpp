#include "reservation_serializer.hpp"
#include "../json_keys.hpp"
#include "../../application/requests/reservation_request.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/hotel_reservation.hpp"
#include "../../application/dto/flight_reservation_data.hpp"
#include "../../application/dto/hotel_reservation_data.hpp"

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

    if (requestType == RequestType::flight)
    {
        FlightReservationData data;
        data.airline = obj[JsonKeys::airline];
        data.from = obj[JsonKeys::from];
        data.to = obj[JsonKeys::to];

        data.date = obj[JsonKeys::date];

        data.adults = obj[JsonKeys::adults];
        data.children = obj[JsonKeys::children];

        data.cost = obj[JsonKeys::cost];
        return std::make_unique<FlightReservation>(data);
    }

    HotelReservationData data;
    data.hotelName = obj[JsonKeys::hotel];

    data.fromDate = obj[JsonKeys::from];
    data.toDate = obj[JsonKeys::to];

    data.city = obj[JsonKeys::city];

    data.roomType = obj[JsonKeys::roomType];

    data.adults = obj[JsonKeys::adults];
    data.children = obj[JsonKeys::children];
    data.rooms = obj[JsonKeys::rooms];

    data.cost = obj[JsonKeys::cost];

    return std::make_unique<HotelReservation>(data);
}