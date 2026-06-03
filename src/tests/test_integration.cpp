#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "domain/entities/customer.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/reservation_category.hpp"
#include "domain/entities/user.hpp"
#include "domain/request_type.hpp"
#include "exception.hpp"
#include "infrastructure/persistence/sql/sql_database.hpp"
#include "infrastructure/serialization/reservation_serializer.hpp"

namespace fs = std::filesystem;

class SqlIntegrationTest : public ::testing::Test
{
  protected:
    fs::path tempDir;
    std::unique_ptr<SqlDatabase> db;

    void SetUp() override
    {
        tempDir = fs::temp_directory_path() / "expedia_sql_test";
        fs::remove_all(tempDir);
        fs::create_directories(tempDir);
        db = std::make_unique<SqlDatabase>((tempDir / "test.db").string());
    }

    void TearDown() override
    {
        db.reset();
        fs::remove_all(tempDir);
    }

    User makeUser()
    {
        return User("", "John", "Doe", "john@test.com", "555-0100", "pass123");
    }

    std::unique_ptr<FlightReservation> makeFlightRes()
    {
        auto res = std::make_unique<FlightReservation>();
        res->setAirline("TestAir");
        res->setFrom("JFK");
        res->setTo("LHR");
        res->setDate("2026-08-01");
        res->setAdults(2);
        res->setChildren(0);
        res->setCost(800.0);
        res->setCategory(ReservationCategory::flight);
        res->setProviderId("test_flight");
        res->setRequestType(RequestType::flight);
        return res;
    }
};

TEST_F(SqlIntegrationTest, SaveAndRetrieveUser)
{
    User user = makeUser();
    db->createUser(user);

    EXPECT_FALSE(user.getId().empty());

    auto found = db->findUserByEmail("john@test.com");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->getEmail(), "john@test.com");
}

TEST_F(SqlIntegrationTest, RejectsDuplicateEmail)
{
    User user1 = makeUser();
    db->createUser(user1);

    User user2("", "Jane", "Doe", "john@test.com", "555-0101", "pass456");
    EXPECT_THROW(db->createUser(user2), ValidationException);
}

TEST_F(SqlIntegrationTest, CustomerCardLifecycle)
{
    User user = makeUser();
    db->createUser(user);

    PaymentCard card("411111111111", "John Doe", "12/28", "123");
    Customer customer(user);
    customer.addCard(card);
    db->updateCustomer(customer);

    auto fetched = db->findCustomerById(user.getId());
    ASSERT_TRUE(fetched.has_value());
    ASSERT_EQ(fetched->getCards().size(), 1);
    EXPECT_EQ(fetched->getCards()[0].getNumber(), "411111111111");
    EXPECT_EQ(fetched->getCards()[0].getOwner(), "John Doe");
}

TEST_F(SqlIntegrationTest, ItineraryWithReservations)
{
    User user = makeUser();
    db->createUser(user);
    auto customer = db->findCustomerById(user.getId());
    ASSERT_TRUE(customer.has_value());

    Itinerary itinerary;
    itinerary.setId("itin_sql_001");
    itinerary.addItem(makeFlightRes());
    itinerary.recalculateCost();

    db->saveItineraryForUser(user.getId(), itinerary);

    std::vector<Itinerary> results = db->findItinerariesByUserId(user.getId());
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getId(), "itin_sql_001");
    ASSERT_EQ(results[0].getReservations().size(), 1);

    auto* flight = dynamic_cast<FlightReservation*>(results[0].getReservations()[0].get());
    ASSERT_NE(flight, nullptr);
    EXPECT_EQ(flight->getAirline(), "TestAir");
    EXPECT_DOUBLE_EQ(flight->totalCost(), 800.0);
}

TEST_F(SqlIntegrationTest, MultipleCustomersWithCards)
{
    std::vector<std::string> userIds;

    for (int i = 0; i < 3; i++)
    {
        User user("", "User" + std::to_string(i), "Last", "user" + std::to_string(i) + "@test.com",
                  "555-0" + std::to_string(i), "pass");
        db->createUser(user);
        userIds.push_back(user.getId());

        PaymentCard card("card" + std::to_string(i), "User" + std::to_string(i), "12/28", "123");
        Customer customer(user);
        customer.addCard(card);
        db->updateCustomer(customer);
    }

    for (int i = 0; i < 3; i++)
    {
        auto customer = db->findCustomerById(userIds[i]);
        ASSERT_TRUE(customer.has_value());
        ASSERT_EQ(customer->getCards().size(), 1);
        EXPECT_EQ(customer->getCards()[0].getNumber(), "card" + std::to_string(i));
    }
}

TEST_F(SqlIntegrationTest, PersistsAcrossSessions)
{
    {
        User user = makeUser();
        db->createUser(user);
        PaymentCard card("5555", "John", "12/28", "123");
        Customer customer(user);
        customer.addCard(card);
        db->updateCustomer(customer);
    }

    db.reset();
    db = std::make_unique<SqlDatabase>((tempDir / "test.db").string());

    auto user = db->findUserByEmail("john@test.com");
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getEmail(), "john@test.com");

    auto fetched = db->findCustomerById(user->getId());
    ASSERT_TRUE(fetched.has_value());
    ASSERT_EQ(fetched->getCards().size(), 1);
    EXPECT_EQ(fetched->getCards()[0].getNumber(), "5555");
}

TEST(SerializerTest, RoundTripFlightReservation)
{
    FlightReservation fr;
    fr.setAirline("TestAir");
    fr.setFrom("JFK");
    fr.setTo("LHR");
    fr.setDate("2026-08-01");
    fr.setAdults(2);
    fr.setChildren(1);
    fr.setCost(1200.0);
    fr.setCategory(ReservationCategory::flight);
    fr.setProviderId("test_flight");
    fr.setRequestType(RequestType::flight);

    ReservationSerializer serializer;
    json j = serializer.toJson(fr);

    auto restored = ReservationSerializer::fromJson(j);
    ASSERT_NE(restored, nullptr);

    auto* restoredFlight = dynamic_cast<FlightReservation*>(restored.get());
    ASSERT_NE(restoredFlight, nullptr);
    EXPECT_EQ(restoredFlight->getAirline(), "TestAir");
    EXPECT_EQ(restoredFlight->getFrom(), "JFK");
    EXPECT_EQ(restoredFlight->getTo(), "LHR");
    EXPECT_DOUBLE_EQ(restoredFlight->totalCost(), 1200.0);
}

TEST(SerializerTest, RoundTripHotelReservation)
{
    HotelReservation hr;
    hr.setHotelName("TestHotel");
    hr.setFromDate("2026-07-01");
    hr.setToDate("2026-07-05");
    hr.setCity("Paris");
    hr.setRoomType("suite");
    hr.setAdults(2);
    hr.setChildren(1);
    hr.setRooms(2);
    hr.setCost(2000.0);
    hr.setCategory(ReservationCategory::hotel);
    hr.setProviderId("test_hotel");
    hr.setRequestType(RequestType::hotel);

    ReservationSerializer serializer;
    json j = serializer.toJson(hr);

    auto restored = ReservationSerializer::fromJson(j);
    ASSERT_NE(restored, nullptr);

    auto* restoredHotel = dynamic_cast<HotelReservation*>(restored.get());
    ASSERT_NE(restoredHotel, nullptr);
    EXPECT_EQ(restoredHotel->getHotelName(), "TestHotel");
    EXPECT_EQ(restoredHotel->getCity(), "Paris");
    EXPECT_DOUBLE_EQ(restoredHotel->totalCost(), 2000.0);
}
