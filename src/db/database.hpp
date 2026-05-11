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
    json getObjectsFromFile(const std::string &) const;
    json getObjectWithId(const std::string &, const std::string &) const;
    std::vector<std::string> readJsonAttributeFromFile(const std::string &, const std::string &) const;
    void writeJsonToFile(const std::string &, json, bool);
    std::vector<User> getUsers(const std::string &) const;
    Customer getCustomer(const User &);
    void updateCustomerInfo(const Customer &);
    void writeJsonArrayToFile(const std::string &, json, bool);
    void deleteObjectWithId(const std::string &path, const std::string &id);
    void saveItinerary(const std::string &, const Itinerary &);
    bool checkUserIsCustomer(const User &);
    std::vector<Itinerary> getCustomerItineraries(const std::string &);
    json getObjectsWithAttribute(const std::string &, const std::string &, const std::string &);
};
