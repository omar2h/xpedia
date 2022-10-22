#include "turkishFlightsManager.h"
#include "APIs/expedia_flights_api.h"

std::vector<Flight> TurkishFlightsManager::search_flights() const
{
    FlightRequest request = getRequest();
    TurkishAirlinesOnlineAPI api{};
    api.SetInfo(request.getDate(), request.getFromCity(), request.getToCity());
    api.SetPassengersInfo(request.getChildren(), request.getAdults());

    std::vector<TurkishFlight> turkishFlights = api.GetAvailableFlights();

    std::vector<Flight> flights{};

    for (const auto &flight_ : turkishFlights)
    {
        Flight flight{};
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.cost);
        flights.push_back(flight);
    }
    return flights;
}

bool TurkishFlightsManager::reserve_flight(const FlightReservation &reservation) const
{
    return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo(), TurkishFlight());
}
