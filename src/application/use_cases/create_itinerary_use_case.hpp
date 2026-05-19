#pragma once

#include <vector>
#include <memory>

#include "../dto/flight_search_input.hpp"
#include "../dto/hotel_search_input.hpp"

class User;
class Itinerary;
class ItineraryItem;
class ReservationRequestFactory;
class ReservationFactory;
class ReservationService;

class CreateItineraryUseCase
{
    ReservationRequestFactory &m_requestFactory;
    ReservationFactory &m_reservationFactory;
    ReservationService &m_reservationService;

public:
    CreateItineraryUseCase(
        ReservationRequestFactory &requestFactory,
        ReservationFactory &reservationFactory,
        ReservationService &reservationService);

    [[nodiscard]] Itinerary createItinerary();

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchFlights(
        const FlightSearchInput &input);

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchHotels(
        const HotelSearchInput &input);

    [[nodiscard]] bool addFlightToItinerary(Itinerary &itinerary,
                                            const FlightSearchInput &input,
                                            const ItineraryItem &selectedItem);

    [[nodiscard]] bool addHotelToItinerary(Itinerary &itinerary,
                                           const HotelSearchInput &input,
                                           const ItineraryItem &selectedItem);
};
