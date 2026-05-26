#include <gtest/gtest.h>
#include "application/services/payment_service.hpp"
#include "application/repositories/i_customer_repository.hpp"
#include "application/payments/payment_strategy.hpp"
#include "domain/entities/payment_card.hpp"
#include "domain/entities/customer.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/itinerary.hpp"

namespace
{
    class StubCustomerRepo : public ICustomerRepository
    {
    public:
        bool customerUpdated = false;

        std::optional<Customer> findById(const std::string &) const override { return std::nullopt; }
        void update(const Customer &) override { customerUpdated = true; }
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
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    Customer customer;
    PaymentCard card("1234", "Test", "12/26", "123");

    processor.addCard(customer, card);

    EXPECT_EQ(customer.getCards().size(), 1);
    EXPECT_EQ(customer.getCards()[0].getNumber(), "1234");
    EXPECT_TRUE(customerRepo.customerUpdated);
}

TEST(PaymentProcessorTest, WithdrawMoneyReturnsTrueOnSuccess)
{
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Customer customer;
    customer.setSelectedCard(card);
    Itinerary itinerary;

    bool result = processor.withdrawMoney(customer, itinerary.totalCost(), 1);
    EXPECT_TRUE(result);
}

TEST(PaymentProcessorTest, WithdrawMoneyReturnsFalseOnFailure)
{
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<NeverPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Customer customer;
    customer.setSelectedCard(card);
    Itinerary itinerary;

    bool result = processor.withdrawMoney(customer, itinerary.totalCost(), 1);
    EXPECT_FALSE(result);
}

TEST(PaymentProcessorTest, MakeReservationsReturnsMinusOneOnPaymentFailure)
{
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<NeverPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Customer customer;
    customer.setSelectedCard(card);
    Itinerary itinerary;

    int result = processor.makeReservations(customer, itinerary, 1);
    EXPECT_EQ(result, -1);
}

TEST(PaymentProcessorTest, MakeReservationsReturnsOneOnSuccess)
{
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return true; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Customer customer;
    customer.setSelectedCard(card);
    Itinerary itinerary;

    int result = processor.makeReservations(customer, itinerary, 1);
    EXPECT_EQ(result, 1);
}

TEST(PaymentProcessorTest, MakeReservationsReturnsZeroWhenConfirmationFails)
{
    StubCustomerRepo customerRepo;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    {
        return std::make_unique<AlwaysPayStrategy>();
    };
    auto confirm = [](const Itinerary &) { return false; };

    PaymentProcessor processor(customerRepo, getPayment, confirm);
    PaymentCard card("1234", "Test", "12/26", "123");
    Customer customer;
    customer.setSelectedCard(card);
    Itinerary itinerary;

    int result = processor.makeReservations(customer, itinerary, 1);
    EXPECT_EQ(result, 0);
}
