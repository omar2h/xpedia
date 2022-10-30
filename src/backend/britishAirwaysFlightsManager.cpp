#include "britishAirwaysFlightsManager.h"
#include "../APIs/expedia_flights_api.h"
#include "../model/flight.h"
#include "../model/flightRequest.h"
#include <iostream>

std::vector<ItineraryItem *> BritishAirwaysFlightsManager::search_reservations() const
{
    FlightRequest const *request = dynamic_cast<FlightRequest *>(getRequest());

    vector<BritishAirwaysFlight> flightsBritishAirways = BritishAirwaysOnlineAPI::GetFlights(request->getFromCity(), request->getDate(), request->getToCity(), request->getAdults(), request->getChildren());
    vector<ItineraryItem *> flights;

    // convert
    for (auto &flight_ : flightsBritishAirways)
    {
        Flight flight;
        flight.setType(ReservationType::britishAirways);
        flight.setReqType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.price);
        flights.push_back(flight.Clone());
    }
    return flights;
}

bool BritishAirwaysFlightsManager::reserve(Reservation *reservation) const
{
    // Just dummy. We should map from reservation to the agency api
    return BritishAirwaysOnlineAPI::ReserveFlight(BritishAirwaysFlight(), BritishAirwaysCustomerInfo());
}