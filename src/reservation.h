#ifndef __RESERVATION_H__
#define __RESERVATION_H__
#include <string>

class Reservation
{
public:
    virtual Reservation *Clone() const = 0;

    virtual double total_cost() const = 0;

    virtual std::string toString() const = 0;

    virtual ~Reservation() = default;
};
#endif // __RESERVATION_H__