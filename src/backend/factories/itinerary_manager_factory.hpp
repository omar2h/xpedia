#pragma once

enum class ReservationType;
class ItineraryManager;
class ItineraryManagerFactory
{
public:
    virtual ItineraryManager *getManager(ReservationType type);

    virtual ~ItineraryManagerFactory() = default;
};
