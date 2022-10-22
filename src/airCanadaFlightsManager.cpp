#include "airCanadaFlightsManager.h"
#include "APIs/expedia_flights_api.h"
#include "flight.h"
#include "flightRequest.h"

std::vector<Flight> AirCanadaFlightsManager::search_flights() const
{
    FlightRequest request = getRequest();
    vector<AirCanadaFlight> flightsAirCanada = AirCanadaOnlineAPI::GetFlights(request.getFromCity(), request.getDate(), request.getToCity(), request.getAdults(), request.getChildren());
    vector<Flight> flights;

    // convert
    for (auto const &flight_ : flightsAirCanada)
    {
        Flight flight;
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.price);

        flights.push_back(flight);
    }
    return flights;
}

bool AirCanadaFlightsManager::reserve_flight(const FlightReservation &reservation) const
{
    // Just dummy. We should map from reservation to the agency api
    return AirCanadaOnlineAPI::ReserveFlight(AirCanadaFlight(), AirCanadaCustomerInfo());
}