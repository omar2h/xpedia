#ifndef __ITINERARYMANAGER_H__
#define __ITINERARYMANAGER_H__
#include <vector>

class ReservationRequest;
class Reservation;

class ItineraryManager
{
    ReservationRequest *request{};

public:
    void setRequest(ReservationRequest *const request_)
    {
        request = request_->Clone();
    }
    virtual std::vector<ItineraryItem *> search_reservations() const = 0;

    virtual bool reserve(Reservation *) const = 0;

    virtual std::string getName() const = 0;

    ReservationRequest *getRequest() const { return request->Clone(); }

    virtual ItineraryManager *Clone() = 0;

    virtual ~ItineraryManager()
    {
        delete request;
        request = nullptr;
    }
};
#endif // __ITINERARYMANAGER_H__