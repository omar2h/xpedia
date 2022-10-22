#ifndef __RESERVATIONREQUEST_H__
#define __RESERVATIONREQUEST_H__
enum RequestType
{
    flight,
    hotel
};

class ReservationRequest
{
public:
    virtual ReservationRequest *Clone() = 0;
};
#endif // __RESERVATIONREQUEST_H__