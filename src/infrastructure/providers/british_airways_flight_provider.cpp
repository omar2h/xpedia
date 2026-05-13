#include "british_airways_flight_provider.hpp"
#include "../../apis/expedia_flights_api.hpp"
#include "../../domain/entities/flight.hpp"
#include "../../application/requests/flight_request.hpp"

std::vector<std::unique_ptr<ItineraryItem>> BritishAirwaysFlightProvider::searchReservations() const
{
    auto req = getRequest();
    FlightRequest const *request = dynamic_cast<FlightRequest *>(req.get());

    vector<BritishAirwaysFlight> flightsBritishAirways = BritishAirwaysOnlineAPI::GetFlights(request->getFromCity(), request->getDate(), request->getToCity(), request->getAdults(), request->getChildren());
    std::vector<std::unique_ptr<ItineraryItem>> flights;

    // convert
    for (auto &flight_ : flightsBritishAirways)
    {
        Flight flight;
        flight.setCategory(ReservationCategory::flight);
        flight.setProviderId("british_airways");
        flight.setRequestType(RequestType::flight);
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
