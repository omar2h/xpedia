#include "flight_reservation.hpp"
#include "../factories/reservation_request_factory.hpp"
#include <sstream>
#include <iostream>

FlightReservation::FlightReservation(
    const FlightReservation &other)
    : airline(other.airline),
      from(other.from),
      to(other.to),
      date(other.date),
      adults(other.adults),
      children(other.children),
      cost(other.cost),
      item(nullptr)
{
    if (other.item)
    {
        item.reset(dynamic_cast<Flight *>(other.item->Clone()));
    }
    if (other.request)
    {
        request = std::make_unique<FlightRequest>(*other.request);
    }
}

FlightReservation &
FlightReservation::operator=(
    const FlightReservation &other)
{
    if (this == &other)
        return *this;

    airline = other.airline;
    from = other.from;
    to = other.to;
    date = other.date;
    adults = other.adults;
    children = other.children;
    cost = other.cost;

    if (other.item)
    {
        item.reset(dynamic_cast<Flight *>(other.item->Clone()));
    }
    else
    {
        item.reset();
    }

    if (other.request)
    {
        request = std::make_unique<FlightRequest>(*other.request);
    }
    else
    {
        request.reset();
    }

    return *this;
}

Reservation *FlightReservation::Clone() const
{
    new FlightReservation(*this);
}

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

std::string FlightReservation::toString2() const
{
    std::ostringstream oss;
    oss << "Airline: " << airline << ", From " << from << " to " << to << " on " << date << "\n";
    oss << " Adults: " << adults << ", children: " << children << "\n";
    oss << " Total Cost:" << cost << "\n";
    return oss.str();
}

void FlightReservation::setRequest(std::unique_ptr<ReservationRequest> request)
{
    this->request.reset(dynamic_cast<FlightRequest *>(request.release()));
}

void FlightReservation::setItem(ItineraryItem *const i)
{
    item.reset(dynamic_cast<Flight *>(i->Clone()));
    setType(i);
    setReqType(i);
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
    obj["reqType"] = getReqType();
    obj["cost"] = total_cost();
    return obj;
}

std::unique_ptr<Reservation> FlightReservation::jsonToReservation(json obj)
{
    std::string airline = obj.value("airline", "not found");
    std::string from = obj.value("from", "not found");
    std::string to = obj.value("to", "not found");
    std::string date = obj.value("date", "not found");
    int adults = obj.value("adults", -1);
    int children = obj.value("children", -1);
    double cost = obj.value("cost", -1);
    setAttributes(airline, from, to, date, adults, children, cost);
    return std::unique_ptr<Reservation>(this->Clone());
}

void FlightReservation::setAttributes(const std::string &airline_, const std::string &from_, const std::string &to_, const std::string &date_, int adults_, int children_, double cost_, const std::string &x, int y)
{
    airline = airline_;
    from = from_;
    to = to_;
    date = date_;
    adults = adults_;
    children = children_;
    cost = cost_;
}
