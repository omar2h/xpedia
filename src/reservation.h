#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <string>

class ItineraryItem;
class ReservationRequest;
class Reservation
{
    // ItineraryItem *item{};
    // ReservationRequest *request{};

public:
    virtual Reservation *Clone() const = 0;

    virtual double total_cost() const = 0;

    virtual std::string toString() const = 0;

    // ReservationRequest *getRequest() const { return request->Clone(); }
    // ItineraryItem *getItem() const { return item->Clone(); }

    virtual void setRequest(ReservationRequest *const) = 0;
    virtual void setItem(ItineraryItem *const) = 0;
    // void setRequest(ReservationRequest *const request_)
    // {
    //     request = request_->Clone();
    // }

    // void setItem(ItineraryItem *const item_)
    // {
    //     item = item_->Clone();
    // }

    virtual ~Reservation() = default;
};
#endif // __RESERVATION_H__