#include <gtest/gtest.h>

#include "application/providers/booking_provider.hpp"
#include "application/services/reservation_service.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/reservation_category.hpp"

#include <memory>

namespace
{
class MockBookingProvider : public BookingProvider
{
  public:
    bool reserve(const Reservation&) const override
    {
        return true;
    }

    std::string getProviderId() const override
    {
        return "mock";
    }
};
} // namespace

TEST(ReservationServiceTest, ConfirmReservationsCallsBookingProvider)
{
    bool providerCalled = false;

    auto getProvider = [&](ReservationCategory, const std::string&) -> std::unique_ptr<BookingProvider>
    {
        providerCalled = true;
        return std::make_unique<MockBookingProvider>();
    };

    ReservationService service(getProvider);

    Itinerary itinerary;
    itinerary.setId("test123");

    auto reservation = std::make_unique<FlightReservation>();
    reservation->setCategory(ReservationCategory::flight);
    reservation->setProviderId("mock");
    itinerary.addItem(std::move(reservation));

    EXPECT_TRUE(service.confirmReservations(itinerary));
    EXPECT_TRUE(providerCalled);
}
