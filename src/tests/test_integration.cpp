#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "infrastructure/persistence/storage/file_storage.hpp"
#include "infrastructure/persistence/database.hpp"
#include "infrastructure/persistence/sql/sql_database.hpp"
#include "infrastructure/serialization/reservation_serializer.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/customer.hpp"
#include "domain/entities/flight_reservation.hpp"
#include "domain/entities/hotel_reservation.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/request_type.hpp"
#include "domain/entities/reservation_category.hpp"
#include "exception.hpp"

namespace fs = std::filesystem;

class IntegrationTest : public ::testing::Test
{
protected:
    fs::path tempDir;

    void SetUp() override
    {
        tempDir = fs::temp_directory_path() / "expedia_test";
        fs::remove_all(tempDir);
        fs::create_directories(tempDir);
        fs::current_path(tempDir);
    }

    void TearDown() override
    {
        fs::current_path(tempDir.parent_path());
        fs::remove_all(tempDir);
    }

    User makeUser()
    {
        return User("u1", "John", "Doe", "john@test.com", "555-0100", "pass123");
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

TEST_F(IntegrationTest, FileStorageFullCycle)
{
    FileStorage storage;

    json obj;
    obj["id"] = "abc123";
    obj["value"] = 42;

    storage.writeJsonToFile("data.json", obj, false);

    json all = storage.readAll("data.json");
    ASSERT_TRUE(all.is_array());
    ASSERT_EQ(all.size(), 1);
    EXPECT_EQ(all[0]["id"], "abc123");
    EXPECT_EQ(all[0]["value"], 42);

    auto attr = storage.readJsonAttributeFromFile("data.json", "id");
    ASSERT_EQ(attr.size(), 1);
    EXPECT_EQ(attr[0], "abc123");

    json found = storage.getObjectWithId("data.json", "abc123");
    EXPECT_FALSE(found.empty());
    EXPECT_EQ(found["value"], 42);

    json missing = storage.getObjectWithId("data.json", "nonexistent");
    EXPECT_TRUE(missing.empty());

    storage.deleteObjectWithId("data.json", "abc123");
    json afterDelete = storage.readAll("data.json");
    EXPECT_TRUE(afterDelete.empty());
}

TEST_F(IntegrationTest, FileStorageEmptyAndMissingFiles)
{
    FileStorage storage;

    json emptyArr = storage.readAll("nonexistent.json");
    EXPECT_TRUE(emptyArr.empty());

    std::vector<std::string> emptyAttr = storage.readJsonAttributeFromFile("nonexistent.json", "id");
    EXPECT_TRUE(emptyAttr.empty());

    json emptyObj = storage.getObjectWithId("nonexistent.json", "x");
    EXPECT_TRUE(emptyObj.empty());

    json emptyObjs = storage.getObjectsWithAttribute("nonexistent.json", "x", "y");
    EXPECT_TRUE(emptyObjs.empty());

    {
        std::ofstream empty("empty.json");
    }

    json emptyRead = storage.readAll("empty.json");
    EXPECT_TRUE(emptyRead.empty());
}

TEST_F(IntegrationTest, DatabaseUserSignupAndLogin)
{
    Database db;

    User user = makeUser();
    db.saveUser(user);

    EXPECT_FALSE(user.getId().empty());

    std::vector<User> users = db.getUsers("users.json");
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getFirstName(), "John");
    EXPECT_EQ(users[0].getEmail(), "john@test.com");
    EXPECT_EQ(users[0].getPassword(), "pass123");
}

TEST_F(IntegrationTest, DatabaseRejectsDuplicateEmail)
{
    Database db;

    User user1 = makeUser();
    db.saveUser(user1);

    User user2("dummy", "Jane", "Doe", "john@test.com", "555-0101", "pass456");
    EXPECT_THROW(db.saveUser(user2), ValidationException);
}

TEST_F(IntegrationTest, DatabaseCustomerLifecycle)
{
    Database db;

    User user = makeUser();
    db.saveUser(user);

    Customer customer = db.getCustomer(user);
    EXPECT_EQ(customer.getId(), user.getId());
    EXPECT_TRUE(customer.getCards().empty());
    EXPECT_TRUE(customer.getItinerariesIds().empty());

    PaymentCard card("411111111111", "John Doe", "12/28", "123");
    customer.addCard(card);
    db.updateCustomerInfo(customer);

    Customer updated = db.getCustomer(user);
    ASSERT_EQ(updated.getCards().size(), 1);
    EXPECT_EQ(updated.getCards()[0].getNumber(), "411111111111");
    EXPECT_EQ(updated.getCards()[0].getOwner(), "John Doe");

    EXPECT_TRUE(db.checkUserIsCustomer(user));
}

TEST_F(IntegrationTest, DatabaseItineraryPersistence)
{
    Database db;

    User user = makeUser();
    db.saveUser(user);

    Itinerary itinerary;
    itinerary.setId("itin_001");
    itinerary.addItem(makeFlightRes());

    db.saveItinerary(user.getId(), itinerary);

    std::vector<Itinerary> itineraries = db.getCustomerItineraries(user.getId());
    ASSERT_EQ(itineraries.size(), 1);
    EXPECT_EQ(itineraries[0].getId(), "itin_001");

    const auto &reservations = itineraries[0].getReservations();
    ASSERT_EQ(reservations.size(), 1);

    auto *flight = dynamic_cast<FlightReservation *>(reservations[0].get());
    ASSERT_NE(flight, nullptr);
    EXPECT_EQ(flight->getAirline(), "TestAir");
    EXPECT_EQ(flight->getFrom(), "JFK");
    EXPECT_DOUBLE_EQ(flight->totalCost(), 800.0);
}

TEST_F(IntegrationTest, MultipleUsersAndItineraries)
{
    Database db;

    for (int i = 0; i < 3; i++)
    {
        User user("", "User" + std::to_string(i), "Last" + std::to_string(i),
                  "user" + std::to_string(i) + "@test.com", "555-0" + std::to_string(i), "pass");
        db.saveUser(user);
    }

    std::vector<User> users = db.getUsers("users.json");
    ASSERT_EQ(users.size(), 3);
}

TEST_F(IntegrationTest, SerializationThroughFileStorage)
{
    FileStorage storage;

    HotelReservation hotel;
    hotel.setHotelName("TestHotel");
    hotel.setFromDate("2026-07-01");
    hotel.setToDate("2026-07-05");
    hotel.setCity("Paris");
    hotel.setRoomType("suite");
    hotel.setAdults(2);
    hotel.setChildren(1);
    hotel.setRooms(2);
    hotel.setCost(2000.0);
    hotel.setCategory(ReservationCategory::hotel);
    hotel.setProviderId("test_hotel");
    hotel.setRequestType(RequestType::hotel);

    ReservationSerializer serializer;
    json j = serializer.toJson(hotel);

    json wrapper = json::array();
    wrapper.push_back(j);
    {
        std::ofstream out("reservations.json");
        out << wrapper.dump(4);
    }

    json readBack;
    {
        std::ifstream in("reservations.json");
        in >> readBack;
    }

    ASSERT_TRUE(readBack.is_array());
    ASSERT_EQ(readBack.size(), 1);

    auto restored = ReservationSerializer::fromJson(readBack[0]);
    ASSERT_NE(restored, nullptr);

    auto *hotelRestored = dynamic_cast<HotelReservation *>(restored.get());
    ASSERT_NE(hotelRestored, nullptr);
    EXPECT_EQ(hotelRestored->getHotelName(), "TestHotel");
    EXPECT_EQ(hotelRestored->getCity(), "Paris");
    EXPECT_EQ(hotelRestored->getRoomType(), "suite");
    EXPECT_EQ(hotelRestored->getAdults(), 2);
    EXPECT_EQ(hotelRestored->getChildren(), 1);
    EXPECT_EQ(hotelRestored->getRooms(), 2);
    EXPECT_DOUBLE_EQ(hotelRestored->totalCost(), 2000.0);
}

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
    db->saveUser(user);

    EXPECT_FALSE(user.getId().empty());

    std::vector<User> users = db->getUsers("");
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getEmail(), "john@test.com");
}

TEST_F(SqlIntegrationTest, RejectsDuplicateEmail)
{
    User user1 = makeUser();
    db->saveUser(user1);

    User user2("", "Jane", "Doe", "john@test.com", "555-0101", "pass456");
    EXPECT_THROW(db->saveUser(user2), ValidationException);
}

TEST_F(SqlIntegrationTest, CustomerCardLifecycle)
{
    User user = makeUser();
    db->saveUser(user);

    PaymentCard card("411111111111", "John Doe", "12/28", "123");
    Customer customer(user);
    customer.addCard(card);
    db->updateCustomerInfo(customer);

    Customer fetched = db->getCustomer(user);
    ASSERT_EQ(fetched.getCards().size(), 1);
    EXPECT_EQ(fetched.getCards()[0].getNumber(), "411111111111");
    EXPECT_EQ(fetched.getCards()[0].getOwner(), "John Doe");
}

TEST_F(SqlIntegrationTest, ItineraryWithReservations)
{
    User user = makeUser();
    db->saveUser(user);
    Customer customer = db->getCustomer(user);

    Itinerary itinerary;
    itinerary.setId("itin_sql_001");
    itinerary.addItem(makeFlightRes());
    itinerary.recalculateCost();

    db->saveItinerary(user.getId(), itinerary);

    std::vector<Itinerary> results = db->getCustomerItineraries(user.getId());
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getId(), "itin_sql_001");
    ASSERT_EQ(results[0].getReservations().size(), 1);

    auto *flight = dynamic_cast<FlightReservation *>(results[0].getReservations()[0].get());
    ASSERT_NE(flight, nullptr);
    EXPECT_EQ(flight->getAirline(), "TestAir");
    EXPECT_DOUBLE_EQ(flight->totalCost(), 800.0);
}

TEST_F(SqlIntegrationTest, MultipleCustomersWithCards)
{
    for (int i = 0; i < 3; i++)
    {
        User user("", "User" + std::to_string(i), "Last",
                  "user" + std::to_string(i) + "@test.com", "555-0" + std::to_string(i), "pass");
        db->saveUser(user);

        PaymentCard card("card" + std::to_string(i), "User" + std::to_string(i), "12/28", "123");
        Customer customer(user);
        customer.addCard(card);
        db->updateCustomerInfo(customer);
    }

    for (int i = 0; i < 3; i++)
    {
        User lookup("", "", "", "user" + std::to_string(i) + "@test.com", "", "");
        Customer customer = db->getCustomer(User(std::to_string(i + 1), "", "", "", "", ""));
        ASSERT_EQ(customer.getCards().size(), 1);
        EXPECT_EQ(customer.getCards()[0].getNumber(), "card" + std::to_string(i));
    }
}

TEST_F(SqlIntegrationTest, PersistsAcrossSessions)
{
    {
        User user = makeUser();
        db->saveUser(user);
        PaymentCard card("5555", "John", "12/28", "123");
        Customer customer(user);
        customer.addCard(card);
        db->updateCustomerInfo(customer);
    }

    db.reset();
    db = std::make_unique<SqlDatabase>((tempDir / "test.db").string());

    std::vector<User> users = db->getUsers("");
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getEmail(), "john@test.com");

    Customer fetched = db->getCustomer(users[0]);
    ASSERT_EQ(fetched.getCards().size(), 1);
    EXPECT_EQ(fetched.getCards()[0].getNumber(), "5555");
}
