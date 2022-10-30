#ifndef __HOTELREQUESTDATAREADER_H__
#define __HOTELREQUESTDATAREADER_H__

#include "requestDataReader.h"
#include "../model/hotelRequest.h"

class HotelRequestDataReader : public RequestDataReader
{
    HotelRequest *hotelRequest{};

public:
    HotelRequestDataReader();
    ReservationRequest *read() override;
    ~HotelRequestDataReader() = default;
};

#endif // __HOTELREQUESTDATAREADER_H__