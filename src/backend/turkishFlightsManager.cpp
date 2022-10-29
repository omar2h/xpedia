#include "turkishFlightsManager.h"
#include "../APIs/expedia_flights_api.h"

std::vector<ItineraryItem *> TurkishFlightsManager::search_reservations() const
{
    const FlightRequest *request = dynamic_cast<FlightRequest *>(getRequest());

    TurkishAirlinesOnlineAPI api{};
    api.SetInfo(request->getDate(), request->getFromCity(), request->getToCity());
    api.SetPassengersInfo(request->getChildren(), request->getAdults());

    std::vector<TurkishFlight> turkishFlights = api.GetAvailableFlights();

    std::vector<ItineraryItem *> flights{};

    for (const auto &flight_ : turkishFlights)
    {
        Flight flight;
        flight.setType(ReservationType::turkish);
        flight.setReqType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.cost);
        flights.push_back(flight.Clone());
    }
    return flights;
}

bool TurkishFlightsManager::reserve(Reservation *reservation) const
{
    return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo(), TurkishFlight());
}
