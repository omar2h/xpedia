#pragma once

#include "../../application/database_interface.hpp"
#include "user_repository.hpp"
#include "customer_repository.hpp"
#include "repositories/itinerary_repository.hpp"
#include "storage/file_storage.hpp"

class Database : public IDatabase
{
    UserRepository userRepository;
    CustomerRepository customerRepository;
    FileStorage storage{};
    ItineraryRepository itineraryRepository;

public:
    Database();

    void saveUser(User &) override;
    [[nodiscard]] std::vector<User> getUsers(const std::string &) const override;
    [[nodiscard]] Customer getCustomer(const User &) override;
    void updateCustomerInfo(const Customer &) override;
    void saveItinerary(const std::string &, const Itinerary &) override;
    [[nodiscard]] bool checkUserIsCustomer(const User &) override;
    [[nodiscard]] std::vector<Itinerary> getCustomerItineraries(const std::string &) override;
};
