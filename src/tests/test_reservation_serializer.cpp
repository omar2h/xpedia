#include <gtest/gtest.h>
#include "infrastructure/serialization/reservation_serializer.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"
#include "domain/entities/reservation_category.hpp"
#include "domain/request_type.hpp"
#include "exception.hpp"

TEST(ReservationSerializerTest, FlightRoundTrip)
{
    FlightReservation original;
    original.setAirline("TestAir");
    original.setFrom("NYC");
    original.setTo("LAX");
    original.setDate("2026-06-01");
    original.setAdults(2);
    original.setChildren(1);
    original.setCost(500.0);
    original.setCategory(ReservationCategory::flight);
    original.setProviderId("test_provider");
    original.setRequestType(RequestType::flight);

    ReservationSerializer serializer;
    json j = serializer.toJson(original);
    auto restored = ReservationSerializer::fromJson(j);

    ASSERT_NE(restored, nullptr);
    auto *flight = dynamic_cast<FlightReservation *>(restored.get());
    ASSERT_NE(flight, nullptr);
    EXPECT_EQ(flight->getAirline(), "TestAir");
    EXPECT_EQ(flight->getFrom(), "NYC");
    EXPECT_EQ(flight->getTo(), "LAX");
    EXPECT_EQ(flight->getDate(), "2026-06-01");
    EXPECT_EQ(flight->getAdults(), 2);
    EXPECT_EQ(flight->getChildren(), 1);
    EXPECT_DOUBLE_EQ(flight->totalCost(), 500.0);
    EXPECT_EQ(flight->getCategory(), ReservationCategory::flight);
    EXPECT_EQ(flight->getProviderId(), "test_provider");
}

TEST(ReservationSerializerTest, HotelRoundTrip)
{
    HotelReservation original;
    original.setHotelName("TestHotel");
    original.setFromDate("2026-07-01");
    original.setToDate("2026-07-05");
    original.setCity("Paris");
    original.setRoomType("suite");
    original.setAdults(2);
    original.setChildren(0);
    original.setRooms(1);
    original.setCost(1200.0);
    original.setCategory(ReservationCategory::hotel);
    original.setProviderId("test_hotel");
    original.setRequestType(RequestType::hotel);

    ReservationSerializer serializer;
    json j = serializer.toJson(original);
    auto restored = ReservationSerializer::fromJson(j);

    ASSERT_NE(restored, nullptr);
    auto *hotel = dynamic_cast<HotelReservation *>(restored.get());
    ASSERT_NE(hotel, nullptr);
    EXPECT_EQ(hotel->getHotelName(), "TestHotel");
    EXPECT_EQ(hotel->getFromDate(), "2026-07-01");
    EXPECT_EQ(hotel->getToDate(), "2026-07-05");
    EXPECT_EQ(hotel->getCity(), "Paris");
    EXPECT_EQ(hotel->getRoomType(), "suite");
    EXPECT_EQ(hotel->getAdults(), 2);
    EXPECT_EQ(hotel->getChildren(), 0);
    EXPECT_EQ(hotel->getRooms(), 1);
    EXPECT_DOUBLE_EQ(hotel->totalCost(), 1200.0);
    EXPECT_EQ(hotel->getCategory(), ReservationCategory::hotel);
    EXPECT_EQ(hotel->getProviderId(), "test_hotel");
}

TEST(ReservationSerializerTest, UnknownCategoryThrows)
{
    json j;
    j["category"] = "car";
    j["providerId"] = "test";
    j["requestType"] = static_cast<int>(RequestType::hotel);

    EXPECT_THROW(ReservationSerializer::fromJson(j), ValidationException);
}

TEST(ReservationSerializerTest, SerializePreservesType)
{
    FlightReservation flight;
    flight.setAirline("Airline");
    flight.setCategory(ReservationCategory::flight);
    flight.setProviderId("bp");
    flight.setRequestType(RequestType::flight);

    json j = ReservationSerializer{}.toJson(flight);
    EXPECT_EQ(j["category"].get<std::string>(), "flight");
    EXPECT_EQ(j["providerId"].get<std::string>(), "bp");
}
