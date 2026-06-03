#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"
#include "domain/factories/reservation_factory.hpp"
#include "domain/request_type.hpp"
#include <gtest/gtest.h>

TEST(ReservationFactoryTest, GetFlightReservation)
{
    ReservationFactory factory;
    auto res = factory.getReservation(RequestType::flight);
    ASSERT_NE(res, nullptr);
    EXPECT_TRUE(dynamic_cast<FlightReservation*>(res.get()) != nullptr);
}

TEST(ReservationFactoryTest, GetHotelReservation)
{
    ReservationFactory factory;
    auto res = factory.getReservation(RequestType::hotel);
    ASSERT_NE(res, nullptr);
    EXPECT_TRUE(dynamic_cast<HotelReservation*>(res.get()) != nullptr);
}

TEST(ReservationFactoryTest, UnknownTypeReturnsNull)
{
    ReservationFactory factory;
    auto res = factory.getReservation(static_cast<RequestType>(999));
    EXPECT_EQ(res, nullptr);
}
