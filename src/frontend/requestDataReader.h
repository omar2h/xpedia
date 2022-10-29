#ifndef __REQUESTDATAREADER_H__
#define __REQUESTDATAREADER_H__
#include "../model/reservationRequest.h"

class RequestDataReader
{
public:
    virtual ReservationRequest *read() = 0;
    virtual ~RequestDataReader() = 0;
};
#endif // __REQUESTDATAREADER_H__