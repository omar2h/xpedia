#include "flightReservation.h"
#include "reservationRequestFactory.h"
#include <sstream>

double FlightReservation::total_cost() const
{
    return item->getTotalCost() * request->getAdults() +
           item->getTotalCost() * request->getChildren() * 0.5;
}

std::string FlightReservation::toString() const
{
    std::ostringstream oss;
    oss << "Airline: " << item->getAirline() << ": From " << request->getFromCity() << " to " << request->getToCity() << " on " << item->getDate() << "\n";
    oss << "Adults: " << request->getAdults() << ", children: " << request->getChildren() << "\n";
    oss << "Total Cost:" << total_cost() << "\n";
    return oss.str();
}

void FlightReservation::setRequest(ReservationRequest *const req)
{
    request = dynamic_cast<FlightRequest *>(req);
}

void FlightReservation::setItem(ItineraryItem *const i)
{
    item = dynamic_cast<Flight *>(i);
    setType(i);
}

json FlightReservation::toJson() const
{
    json obj;
    obj["airline"] = item->getAirline();
    obj["from"] = request->getFromCity();
    obj["to"] = request->getToCity();
    obj["date"] = item->getDate();
    obj["adults"] = request->getAdults();
    obj["children"] = request->getChildren();
    obj["type"] = getType();
    return obj;
}
