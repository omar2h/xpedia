#include "create_empty_itinerary_use_case.hpp"

#include "../../domain/entities/itinerary.hpp"
#include "../../util/id_generator.hpp"

Itinerary CreateEmptyItineraryUseCase::execute() const
{
    Itinerary itinerary;
    itinerary.setId(generateId());
    return itinerary;
}
