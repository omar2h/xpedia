#ifndef __RESERVATIONREQUEST_H__
#define __RESERVATIONREQUEST_H__
#include <string>

enum class RequestType
{
    flight,
    hotel
};

class ReservationRequest
{
public:
    virtual ReservationRequest *Clone() = 0;
    virtual std::string toString() const = 0;
};
#endif // __RESERVATIONREQUEST_H__