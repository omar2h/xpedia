#include <gtest/gtest.h>

#include "application/providers/booking_provider.hpp"
#include "application/providers/hotel_search_provider.hpp"
#include "application/services/reservation_service.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_room.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/reservation_category.hpp"
#include "domain/value_objects/hotel_search_request.hpp"

#include <memory>
#include <vector>

namespace
{
    class MockHotelProvider : public HotelSearchProvider
    {
    public:
        std::vector<std::unique_ptr<ItineraryItem>>
        searchHotels(const HotelSearchRequest &request) override
        {
            std::vector<std::unique_ptr<ItineraryItem>> items;

            auto room = std::make_unique<HotelRoom>();
            room->setHotelName("MockHotel");
            room->setDateFrom(request.checkInDate);
            room->setDateTo(request.checkOutDate);
            room->setPricePerNight(150);
            room->setCategory(ReservationCategory::hotel);
            room->setProviderId("mock_hotel");

            items.push_back(std::move(room));
            return items;
        }

        bool reserve(Reservation *) override { return true; }

        std::string getName() const override { return "MockHotel"; }
    };

    class MockBookingProvider : public BookingProvider
    {
    public:
        bool reserve(const Reservation &) const override { return true; }

        std::string getProviderId() const override { return "mock"; }
    };
}

TEST(ReservationServiceTest, SearchHotelsReturnsProviderItems)
{
    auto getProviders = [] {
        std::vector<std::unique_ptr<HotelSearchProvider>> providers;
        providers.push_back(std::make_unique<MockHotelProvider>());
        return providers;
    };

    auto getProvider = [](ReservationCategory, const std::string &) -> std::unique_ptr<BookingProvider> {
        return nullptr;
    };

    ReservationService service(getProviders, getProvider);

    HotelSearchRequest request;
    request.city = "Paris";
    request.checkInDate = "2026-07-01";
    request.checkOutDate = "2026-07-05";
    request.adults = 2;
    request.rooms = 1;

    auto items = service.searchHotels(request);

    ASSERT_EQ(items.size(), 1);
    auto *hotel = dynamic_cast<HotelRoom *>(items[0].get());
    ASSERT_NE(hotel, nullptr);
    EXPECT_EQ(hotel->getHotelName(), "MockHotel");
    EXPECT_EQ(hotel->getDateFrom(), "2026-07-01");
    EXPECT_DOUBLE_EQ(hotel->getPricePerNight(), 150);
}

TEST(ReservationServiceTest, ConfirmReservationsCallsBookingProvider)
{
    bool providerCalled = false;

    auto getProviders = [] {
        return std::vector<std::unique_ptr<HotelSearchProvider>>{};
    };

    auto getProvider = [&](ReservationCategory, const std::string &) -> std::unique_ptr<BookingProvider> {
        providerCalled = true;
        return std::make_unique<MockBookingProvider>();
    };

    ReservationService service(getProviders, getProvider);

    Itinerary itinerary;
    itinerary.setId("test123");

    auto reservation = std::make_unique<FlightReservation>();
    reservation->setCategory(ReservationCategory::flight);
    reservation->setProviderId("mock");
    itinerary.addItem(std::move(reservation));

    EXPECT_TRUE(service.confirmReservations(itinerary));
    EXPECT_TRUE(providerCalled);
}
