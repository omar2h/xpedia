#include "air_france_flight_provider.hpp"
#include "../apis/expedia_flights_api.hpp"
#include "../../domain/entities/flight.hpp"
#include "../../domain/requests/flight_request.hpp"

std::vector<std::unique_ptr<ItineraryItem>> AirFranceFlightProvider::searchReservations() const
{
    auto req = getRequest();
    const FlightRequest &request = dynamic_cast<const FlightRequest &>(*req);

    AirFranceOnlineAPI api{};
    api.SetInfo(request.getDate(), request.getFromCity(), request.getToCity());
    api.SetPassengersInfo(request.getChildren(), request.getAdults());

    std::vector<AirFranceFlight> airFranceFlights = api.GetAvailableFlights();

    std::vector<std::unique_ptr<ItineraryItem>> flights{};

    for (const auto &flight_ : airFranceFlights)
    {
        Flight flight;
        flight.setCategory(ReservationCategory::flight);
        flight.setProviderId("air_france");
        flight.setRequestType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.cost);
        flights.push_back(flight.clone());
    }
    return flights;
}

bool AirFranceFlightProvider::reserve(Reservation *reservation) const
{
    return AirFranceOnlineAPI::ReserveFlight(AirFranceCustomerInfo(), AirFranceFlight());
}
