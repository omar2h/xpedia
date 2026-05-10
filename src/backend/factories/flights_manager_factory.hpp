#pragma once

#include "itinerary_manager_factory.hpp"
#include "../managers/flights_manager.hpp"
#include <vector>

enum class ReservationType;
class FlightsManagerFactory : public ItineraryManagerFactory
{
public:
    std::unique_ptr<ItineraryManager> getManager(ReservationType) override;
    static std::vector<std::unique_ptr<ItineraryManager>> getManagers();
};
