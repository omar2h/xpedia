#pragma once

#include <memory>

enum class ReservationType;
class ItineraryManager;
class ItineraryManagerFactory
{
public:
    virtual std::unique_ptr<ItineraryManager> getManager(ReservationType type);

    virtual ~ItineraryManagerFactory() = default;
};
