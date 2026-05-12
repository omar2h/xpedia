#include <gtest/gtest.h>
#include "application/services/payment_service.hpp"
#include "application/database_interface.hpp"
#include "application/payments/payment_strategy.hpp"
#include "domain/entities/payment_card.hpp"
#include "domain/entities/customer.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/itinerary.hpp"

namespace
{
    class StubDatabase : public IDatabase
    {
    public:
        bool customerUpdated = false;

        void saveUser(User &) override {}
        std::vector<User> getUsers(const std::string &) const override { return {}; }
        Customer getCustomer(const User &) override { return Customer{}; }
        void updateCustomerInfo(const Customer &) override { customerUpdated = true; }
        void saveItinerary(const std::string &, const Itinerary &) override {}
        bool checkUserIsCustomer(const User &) override { return false; }
        std::vector<Itinerary> getCustomerItineraries(const std::string &) override { return {}; }
    };

    class AlwaysPayStrategy : public PaymentStrategy
    {
    public:
        bool pay(const PaymentCard &, double) override { return true; }
    };

    class NeverPayStrategy : public PaymentStrategy
    {
    public:
        bool pay(const PaymentCard &, double) override { return false; }
    };
}

TEST(PaymentProcessorTest, AddCardUpdatesDatabase)
{
    StubDatabase db;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(db, getPayment, confirm);
    Customer customer;
    PaymentCard card("1234", "Test", "12/26", "123");

    processor.addCard(customer, card);

    EXPECT_EQ(customer.getCards().size(), 1);
    EXPECT_EQ(customer.getCards()[0].getNumber(), "1234");
    EXPECT_TRUE(db.customerUpdated);
}

TEST(PaymentProcessorTest, WithdrawMoneyReturnsTrueOnSuccess)
{
    StubDatabase db;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(db, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Itinerary itinerary;

    bool result = processor.withdrawMoney(card, 1, itinerary);
    EXPECT_TRUE(result);
}

TEST(PaymentProcessorTest, WithdrawMoneyReturnsFalseOnFailure)
{
    StubDatabase db;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<NeverPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(db, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Itinerary itinerary;

    bool result = processor.withdrawMoney(card, 1, itinerary);
    EXPECT_FALSE(result);
}

TEST(PaymentProcessorTest, MakeReservationsReturnsMinusOneOnPaymentFailure)
{
    StubDatabase db;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<NeverPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(db, getPayment, confirm);
    Customer customer;
    PaymentCard card("1234", "Test", "12/26", "123");
    Itinerary itinerary;

    int result = processor.makeReservations(customer, card, 1, itinerary);
    EXPECT_EQ(result, -1);
}

TEST(PaymentProcessorTest, MakeReservationsReturnsOneOnSuccess)
{
    StubDatabase db;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(db, getPayment, confirm);
    Customer customer;
    PaymentCard card("1234", "Test", "12/26", "123");
    Itinerary itinerary;

    int result = processor.makeReservations(customer, card, 1, itinerary);
    EXPECT_EQ(result, 1);
}
