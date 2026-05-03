#ifndef __HOTELREQUESTDATAREADER_H__
#define __HOTELREQUESTDATAREADER_H__

#include "request_data_reader.h"
#include "../model/requests/hotel_request.h"

class HotelRequestDataReader : public RequestDataReader
{
    HotelRequest *hotelRequest{};

public:
    HotelRequestDataReader();
    ReservationRequest *read() override;
    ~HotelRequestDataReader() = default;
};

#endif // __HOTELREQUESTDATAREADER_H__
