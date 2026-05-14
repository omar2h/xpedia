#include <gtest/gtest.h>
#include "application/use_cases/create_itinerary_use_case.hpp"
#include "application/factories/reservation_request_factory.hpp"
#include "application/services/reservation_service.hpp"
#include "domain/factories/reservation_factory.hpp"
#include "domain/entities/flight.hpp"
#include "domain/entities/hotel_room.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/reservation_category.hpp"
#include "application/providers/reservation_provider.hpp"
#include "domain/requests/flight_request.hpp"
#include "domain/requests/hotel_request.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"

namespace
{
    class StubFlightProvider : public ReservationProvider
    {
    public:
        std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override
        {
            return {};
        }

        bool reserve(Reservation *) const override { return true; }
        std::string getName() const override { return "Stub"; }
        std::string getCategory() const override { return "flight"; }
    };

    std::unique_ptr<Flight> makeFlight(const std::string &airline, const std::string &date, double cost)
    {
        auto flight = std::make_unique<Flight>();
        flight->setAirline(airline);
        flight->setDate(date);
        flight->setTotalCost(cost);
        flight->setCategory(ReservationCategory::flight);
        flight->setProviderId("stub_airline");
        flight->setRequestType(RequestType::flight);
        return flight;
    }

    std::unique_ptr<HotelRoom> makeHotelRoom(const std::string &name, const std::string &from, const std::string &to, double price)
    {
        auto room = std::make_unique<HotelRoom>();
        room->setHotelName(name);
        room->setDateFrom(from);
        room->setDateTo(to);
        room->setPricePerNight(price);
        room->setCategory(ReservationCategory::hotel);
        room->setProviderId("stub_hotel");
        room->setRequestType(RequestType::hotel);
        return room;
    }
}

TEST(CreateItineraryTest, CreateItineraryGeneratesId)
{
    ReservationRequestFactory reqFactory;
    ReservationFactory resFactory;
    auto getProviders = [](ReservationCategory) { return std::vector<std::unique_ptr<ReservationProvider>>{}; };
    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        return nullptr;
    };
    ReservationService service(getProviders, getProvider);
    CreateItineraryUseCase useCase(reqFactory, resFactory, service);

    Itinerary itinerary = useCase.createItinerary();

    EXPECT_FALSE(itinerary.getId().empty());
}

TEST(CreateItineraryTest, AddFlightItemToItinerary)
{
    ReservationRequestFactory reqFactory;
    ReservationFactory resFactory;
    auto getProviders = [](ReservationCategory) { return std::vector<std::unique_ptr<ReservationProvider>>{}; };
    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        return nullptr;
    };
    ReservationService service(getProviders, getProvider);
    CreateItineraryUseCase useCase(reqFactory, resFactory, service);

    Itinerary itinerary = useCase.createItinerary();

    auto flightReq = std::make_unique<FlightRequest>("JFK", "LHR", "2026-08-01", 1, 0);
    auto selectedFlight = makeFlight("BA", "2026-08-01", 800);

    useCase.addItemToItinerary(itinerary, RequestType::flight, std::move(flightReq), *selectedFlight);

    const auto &reservations = itinerary.getReservations();
    ASSERT_EQ(reservations.size(), 1);
    auto *flightRes = dynamic_cast<FlightReservation *>(reservations[0].get());
    ASSERT_NE(flightRes, nullptr);
    EXPECT_EQ(flightRes->getFrom(), "JFK");
    EXPECT_EQ(flightRes->getTo(), "LHR");
    EXPECT_EQ(flightRes->getAirline(), "BA");
    EXPECT_EQ(flightRes->getDate(), "2026-08-01");
    EXPECT_EQ(flightRes->getAdults(), 1);
    EXPECT_EQ(flightRes->getChildren(), 0);
}

TEST(CreateItineraryTest, AddHotelItemToItinerary)
{
    ReservationRequestFactory reqFactory;
    ReservationFactory resFactory;
    auto getProviders = [](ReservationCategory) { return std::vector<std::unique_ptr<ReservationProvider>>{}; };
    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        return nullptr;
    };
    ReservationService service(getProviders, getProvider);
    CreateItineraryUseCase useCase(reqFactory, resFactory, service);

    Itinerary itinerary = useCase.createItinerary();

    auto hotelReq = std::make_unique<HotelRequest>("2026-09-01", "2026-09-05", "Tokyo", 2, 1);
    hotelReq->setRooms(1);
    auto selectedRoom = makeHotelRoom("TokoyoInn", "2026-09-01", "2026-09-05", 200);

    useCase.addItemToItinerary(itinerary, RequestType::hotel, std::move(hotelReq), *selectedRoom);

    const auto &reservations = itinerary.getReservations();
    ASSERT_EQ(reservations.size(), 1);
    auto *hotelRes = dynamic_cast<HotelReservation *>(reservations[0].get());
    ASSERT_NE(hotelRes, nullptr);
    EXPECT_EQ(hotelRes->getCity(), "Tokyo");
    EXPECT_EQ(hotelRes->getHotelName(), "TokoyoInn");
    EXPECT_EQ(hotelRes->getAdults(), 2);
    EXPECT_EQ(hotelRes->getChildren(), 1);
    EXPECT_EQ(hotelRes->getRooms(), 1);
}
