#pragma once

#include "request_data_reader.hpp"
#include "../model/requests/hotel_request.hpp"

class HotelRequestDataReader : public RequestDataReader
{
    HotelRequest *hotelRequest{};

public:
    HotelRequestDataReader();
    ReservationRequest *read() override;
    ~HotelRequestDataReader() = default;
};
