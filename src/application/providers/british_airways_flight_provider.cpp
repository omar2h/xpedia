#include "british_airways_flight_provider.hpp"
#include "../../apis/expedia_flights_api.hpp"
#include "../../model/flight.hpp"
#include "../../model/requests/flight_request.hpp"
#include <iostream>

std::vector<std::unique_ptr<ItineraryItem>> BritishAirwaysFlightProvider::search_reservations() const
{
    FlightRequest const *request = dynamic_cast<FlightRequest *>(getRequest());

    vector<BritishAirwaysFlight> flightsBritishAirways = BritishAirwaysOnlineAPI::GetFlights(request->getFromCity(), request->getDate(), request->getToCity(), request->getAdults(), request->getChildren());
    std::vector<std::unique_ptr<ItineraryItem>> flights;

    // convert
    for (auto &flight_ : flightsBritishAirways)
    {
        Flight flight;
        flight.setType(ReservationType::britishAirways);
        flight.setReqType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.price);
        flights.push_back(flight.clone());
    }
    return flights;
}

bool BritishAirwaysFlightProvider::reserve(Reservation *reservation) const
{
    // Just dummy. We should map from reservation to the agency api
    return BritishAirwaysOnlineAPI::ReserveFlight(BritishAirwaysFlight(), BritishAirwaysCustomerInfo());
}
