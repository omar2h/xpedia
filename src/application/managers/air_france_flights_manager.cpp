#include "air_france_flights_manager.hpp"
#include "../../apis/expedia_flights_api.hpp"

std::vector<std::unique_ptr<ItineraryItem>> AirFranceFlightsManager::search_reservations() const
{
    const FlightRequest *request = dynamic_cast<FlightRequest *>(getRequest());

    AirFranceOnlineAPI api{};
    api.SetInfo(request->getDate(), request->getFromCity(), request->getToCity());
    api.SetPassengersInfo(request->getChildren(), request->getAdults());

    std::vector<AirFranceFlight> airFranceFlights = api.GetAvailableFlights();

    std::vector<std::unique_ptr<ItineraryItem>> flights{};

    for (const auto &flight_ : airFranceFlights)
    {
        Flight flight;
        flight.setType(ReservationType::airFrance);
        flight.setReqType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.cost);
        flights.push_back(flight.clone());
    }
    return flights;
}

bool AirFranceFlightsManager::reserve(Reservation *reservation) const
{
    return AirFranceOnlineAPI::ReserveFlight(AirFranceCustomerInfo(), AirFranceFlight());
}
