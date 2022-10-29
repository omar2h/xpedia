#ifndef __FLIGHTREQUESTDATAREADER_H__
#define __FLIGHTREQUESTDATAREADER_H__
#include "requestDataReader.h"
#include "../model/flightRequest.h"

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