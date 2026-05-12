#include <gtest/gtest.h>
#include "application/services/reservation_service.hpp"
#include "application/providers/reservation_provider.hpp"
#include "domain/entities/flight.hpp"
#include "domain/entities/hotel_room.hpp"
#include "domain/request_type.hpp"
#include "application/requests/flight_request.hpp"
#include "application/requests/hotel_request.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"
#include "domain/entities/reservation_category.hpp"
#include "domain/entities/itinerary.hpp"
#include <vector>

namespace
{
    class MockFlightProvider : public ReservationProvider
    {
    public:
        std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override
        {
            std::vector<std::unique_ptr<ItineraryItem>> items;
            auto flight = std::make_unique<Flight>();
            flight->setAirline("MockAir");
            flight->setTotalCost(300);
            items.push_back(std::move(flight));
            return items;
        }

        bool reserve(Reservation *) const override { return true; }
        std::string getName() const override { return "MockFlight"; }
        std::unique_ptr<ReservationProvider> clone() const override
        {
            return std::make_unique<MockFlightProvider>(*this);
        }
    };

    class MockHotelProvider : public ReservationProvider
    {
    public:
        std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override
        {
            std::vector<std::unique_ptr<ItineraryItem>> items;
            auto room = std::make_unique<HotelRoom>();
            room->setHotelName("MockHotel");
            room->setPricePerNight(150);
            items.push_back(std::move(room));
            return items;
        }

        bool reserve(Reservation *) const override { return true; }
        std::string getName() const override { return "MockHotel"; }
        std::unique_ptr<ReservationProvider> clone() const override
        {
            return std::make_unique<MockHotelProvider>(*this);
        }
    };
}

TEST(ReservationServiceTest, GetFlightReservationsReturnsProviderItems)
{
    auto getFlights = []() -> std::vector<std::unique_ptr<ReservationProvider>>
    {
        std::vector<std::unique_ptr<ReservationProvider>> providers;
        providers.push_back(std::make_unique<MockFlightProvider>());
        return providers;
    };
    auto getHotels = []() -> std::vector<std::unique_ptr<ReservationProvider>>
    {
        return {};
    };
    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        return nullptr;
    };

    ReservationService service(getFlights, getHotels, getProvider);
    FlightRequest request("NYC", "LAX", "2026-06-01", 1, 0);
    auto items = service.getAvailableReservations(&request, RequestType::flight);

    ASSERT_EQ(items.size(), 1);
    auto *flight = dynamic_cast<Flight *>(items[0].get());
    ASSERT_NE(flight, nullptr);
    EXPECT_EQ(flight->getAirline(), "MockAir");
    EXPECT_DOUBLE_EQ(flight->getTotalCost(), 300);
}

TEST(ReservationServiceTest, GetHotelReservationsReturnsProviderItems)
{
    auto getFlights = []() -> std::vector<std::unique_ptr<ReservationProvider>>
    {
        return {};
    };
    auto getHotels = []() -> std::vector<std::unique_ptr<ReservationProvider>>
    {
        std::vector<std::unique_ptr<ReservationProvider>> providers;
        providers.push_back(std::make_unique<MockHotelProvider>());
        return providers;
    };
    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        return nullptr;
    };

    ReservationService service(getFlights, getHotels, getProvider);
    HotelRequest request("2026-07-01", "2026-07-05", "Paris", 2, 0);
    auto items = service.getAvailableReservations(&request, RequestType::hotel);

    ASSERT_EQ(items.size(), 1);
    auto *hotel = dynamic_cast<HotelRoom *>(items[0].get());
    ASSERT_NE(hotel, nullptr);
    EXPECT_EQ(hotel->getHotelName(), "MockHotel");
    EXPECT_DOUBLE_EQ(hotel->getPricePerNight(), 150);
}

TEST(ReservationServiceTest, ConfirmReservationsCallsProvider)
{
    bool providerCalled = false;
    auto getFlights = []() { return std::vector<std::unique_ptr<ReservationProvider>>{}; };
    auto getHotels = []() { return std::vector<std::unique_ptr<ReservationProvider>>{}; };
    auto getProvider = [&](ReservationCategory, const std::string &) -> std::unique_ptr<ReservationProvider>
    {
        providerCalled = true;
        return std::make_unique<MockFlightProvider>();
    };

    ReservationService service(getFlights, getHotels, getProvider);
    Itinerary itinerary;
    itinerary.setId("test123");
    FlightReservation res;
    res.setCategory(ReservationCategory::flight);
    res.setProviderId("mock");
    auto clone = res.clone();
    itinerary.addItem(std::move(clone));

    bool result = service.confirmReservations(itinerary);

    EXPECT_TRUE(result);
    EXPECT_TRUE(providerCalled);
}
