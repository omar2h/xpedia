#pragma once

#include <string>

class Reservation;

class BookingProvider
{
  public:
    virtual bool reserve(const Reservation& reservation) const = 0;

    virtual std::string getProviderId() const = 0;

    virtual ~BookingProvider() = default;
};