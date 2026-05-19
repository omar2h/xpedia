#ifndef SRC_INFRASTRUCTURE_APIS_FLIGHTS_FLIGHT_SEARCH_STATUS_HPP_
#define SRC_INFRASTRUCTURE_APIS_FLIGHTS_FLIGHT_SEARCH_STATUS_HPP_

namespace travel_booking_system
{
    namespace infrastructure
    {
        namespace apis
        {
            namespace flights
            {

                enum class FlightSearchStatus
                {
                    Success,
                    NoResults,
                    NetworkError,
                    AuthenticationError,
                    RateLimited,
                    ParseError
                };

            } // namespace flights
        } // namespace apis
    } // namespace infrastructure
} // namespace travel_booking_system

#endif // SRC_INFRASTRUCTURE_APIS_FLIGHTS_FLIGHT_SEARCH_STATUS_HPP_