#ifndef __FLIGHTREQUESTDATAREADER_H__
#define __FLIGHTREQUESTDATAREADER_H__
#include "request_data_reader.h"
#include "../model/requests/flight_request.h"

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
#endif // __FLIGHTREQUESTDATAREADER_H__
