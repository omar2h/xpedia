#pragma once

#include "request_data_reader.hpp"
#include "../model/requests/flight_request.hpp"

class FlightRequestDataReader : public RequestDataReader
{
    FlightRequest *request{};

public:
    FlightRequestDataReader();
    ReservationRequest *read() override;
    ~FlightRequestDataReader() override
    {
    }
};
