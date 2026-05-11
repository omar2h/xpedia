#pragma once

#include "user_repository.hpp"
#include "customer_repository.hpp"
#include "../model/customer.hpp"
#include "../model/itinerary.hpp"
#include "repositories/itinerary_repository.hpp"
#include "storage/file_storage.hpp"
#include <string>
#include <vector>

class Database
{
    UserRepository userRepository;
    CustomerRepository customerRepository;
    FileStorage storage{};
    ItineraryRepository itineraryRepository;

public:
    Database();

    void saveUser(User &);
    [[nodiscard]] std::vector<User> getUsers(const std::string &) const;
    [[nodiscard]] Customer getCustomer(const User &);
    void updateCustomerInfo(const Customer &);
    void saveItinerary(const std::string &, const Itinerary &);
    [[nodiscard]] bool checkUserIsCustomer(const User &);
    [[nodiscard]] std::vector<Itinerary> getCustomerItineraries(const std::string &);
};
