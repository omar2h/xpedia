#pragma once

#include <string>

struct PayItineraryResult
{
    enum Status
    {
        Confirmed,
        Failed,
        NoReservations
    };
    Status status;
    std::string message;
};
