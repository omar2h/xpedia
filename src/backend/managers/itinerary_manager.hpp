#pragma once

#include <vector>

class ReservationRequest;
class Reservation;

class ItineraryManager
{
    ReservationRequest *request{};

public:
    void setRequest(ReservationRequest *const request_)
    {
        request = request_->clone();
    }
    virtual std::vector<std::unique_ptr<ItineraryItem>> search_reservations() const = 0;

    virtual bool reserve(Reservation *) const = 0;

    virtual std::string getName() const = 0;

    ReservationRequest *getRequest() const { return request->clone(); }

    virtual ItineraryManager *clone() = 0;

    virtual ~ItineraryManager()
    {
    }
};
