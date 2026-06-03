#include "application/payments/payment_strategy.hpp"
#include "application/repositories/i_customer_repository.hpp"
#include "application/repositories/i_itinerary_repository.hpp"
#include "application/services/payment_service.hpp"
#include "application/use_cases/pay_itinerary_use_case.hpp"
#include "domain/entities/customer.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/payment_card.hpp"
#include "domain/entities/user.hpp"
#include <gtest/gtest.h>

namespace
{
class StubCustomerRepository : public ICustomerRepository
{
  public:
    std::optional<Customer> storedCustomer;
    bool updateCalled = false;

    std::optional<Customer> findById(const std::string&) const override
    {
        return storedCustomer;
    }

    void update(const Customer& customer) override
    {
        storedCustomer = customer;
        updateCalled = true;
    }
};

class StubItineraryRepository : public IItineraryRepository
{
  public:
    bool saveCalled = false;
    std::string savedUserId;
    std::optional<Itinerary> savedItinerary;

    void save(const std::string& userId, const Itinerary& itinerary) override
    {
        saveCalled = true;
        savedUserId = userId;
        savedItinerary = itinerary;
    }

    std::vector<Itinerary> findByUserId(const std::string&) const override
    {
        return {};
    }
};

class AlwaysPayStrategy : public PaymentStrategy
{
  public:
    bool pay(const PaymentCard&, double) override
    {
        return true;
    }
};

class NeverPayStrategy : public PaymentStrategy
{
  public:
    bool pay(const PaymentCard&, double) override
    {
        return false;
    }
};

Customer makeCustomer()
{
    User user("user-1", "John", "Doe", "john@example.com", "0100", "secret");
    Customer customer(user);
    customer.setSelectedCard(PaymentCard("4111111111111111", "John Doe", "12/27", "123"));
    return customer;
}

Itinerary makeItinerary()
{
    Itinerary itinerary;
    itinerary.setId("it-1");
    itinerary.setCost(1250.0);
    return itinerary;
}
} // namespace

TEST(PayItineraryUseCaseTest, ExecuteSavesItineraryAndUpdatesCustomerOnSuccess)
{
    StubCustomerRepository customerRepository;
    StubItineraryRepository itineraryRepository;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    { return std::make_unique<AlwaysPayStrategy>(); };
    auto confirm = [](const Itinerary&) { return true; };

    PaymentProcessor paymentProcessor(customerRepository, getPayment, confirm);
    PayItineraryUseCase useCase(customerRepository, itineraryRepository, paymentProcessor);

    Customer customer = makeCustomer();
    Itinerary itinerary = makeItinerary();

    auto result = useCase.execute(customer, itinerary, 1);

    EXPECT_TRUE(result.isSuccess());
    EXPECT_TRUE(itineraryRepository.saveCalled);
    EXPECT_EQ(itineraryRepository.savedUserId, customer.getId());
    ASSERT_TRUE(itineraryRepository.savedItinerary.has_value());
    EXPECT_EQ(itineraryRepository.savedItinerary->getId(), itinerary.getId());
    EXPECT_TRUE(customerRepository.updateCalled);
    ASSERT_EQ(customer.getItinerariesIds().size(), 1);
    EXPECT_EQ(customer.getItinerariesIds()[0], itinerary.getId());
}

TEST(PayItineraryUseCaseTest, ExecuteDoesNotPersistWhenPaymentFails)
{
    StubCustomerRepository customerRepository;
    StubItineraryRepository itineraryRepository;
    auto getPayment = [](PaymentService) -> std::unique_ptr<PaymentStrategy>
    { return std::make_unique<NeverPayStrategy>(); };
    auto confirm = [](const Itinerary&) { return true; };

    PaymentProcessor paymentProcessor(customerRepository, getPayment, confirm);
    PayItineraryUseCase useCase(customerRepository, itineraryRepository, paymentProcessor);

    Customer customer = makeCustomer();
    Itinerary itinerary = makeItinerary();

    auto result = useCase.execute(customer, itinerary, 1);

    EXPECT_FALSE(result.isSuccess());
    EXPECT_EQ(result.error(), "Payment failed. Itinerary was not saved.");
    EXPECT_FALSE(itineraryRepository.saveCalled);
    EXPECT_FALSE(customerRepository.updateCalled);
    EXPECT_TRUE(customer.getItinerariesIds().empty());
}
