#include "airCanadaFlightsManager.h"
#include "APIs/expedia_flights_api.h"
#include "flight.h"
#include "flightRequest.h"
#include <iostream>

std::vector<ItineraryItem *> AirCanadaFlightsManager::search_reservations() const
{
    FlightRequest const *request = dynamic_cast<FlightRequest *>(getRequest());

    vector<AirCanadaFlight> flightsAirCanada = AirCanadaOnlineAPI::GetFlights(request->getFromCity(), request->getDate(), request->getToCity(), request->getAdults(), request->getChildren());
    vector<ItineraryItem *> flights;

    // convert
    for (auto &flight_ : flightsAirCanada)
    {
        Flight flight;
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.price);
        flights.push_back(flight.Clone());
    }
    return flights;
}

bool AirCanadaFlightsManager::reserve(Reservation *reservation) const
{
    // Just dummy. We should map from reservation to the agency api
    return AirCanadaOnlineAPI::ReserveFlight(AirCanadaFlight(), AirCanadaCustomerInfo());
}