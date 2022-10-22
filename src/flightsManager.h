#ifndef __FLIGHTSMANAGER_H__
#define __FLIGHTSMANAGER_H__

#include "flightRequest.h"
#include "flightReservation.h"
#include "flight.h"
#include <vector>

class FlightsManager
{
    FlightRequest request{};

public:
    virtual void setFlightRequest(const FlightRequest &request_)
    {
        request = request_;
    }
    virtual std::vector<Flight> search_flights() const = 0;

    virtual bool reserve_flight(const FlightReservation &reservation) const = 0;

    virtual std::string getName() const = 0;

    FlightRequest getRequest() const { return request; }

    virtual ~FlightsManager()
    {
    }
};
#endif // __FLIGHTSMANAGER_H__