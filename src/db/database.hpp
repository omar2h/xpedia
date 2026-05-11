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

    void save_user(User &);
    json get_objects_from_file(const std::string &) const;
    json get_object_with_id(const std::string &, const std::string &) const;
    std::vector<std::string> read_json_attribute_from_file(const std::string &, const std::string &) const;
    void write_json_to_file(const std::string &, json, bool);
    std::vector<User> get_users(const std::string &) const;
    Customer getCustomer(const User &);
    void update_customer_info(const Customer &);
    void write_json_array_to_file(const std::string &, json, bool);
    void delete_object_with_id(const std::string &path, const std::string &id);
    void save_itinerary(const std::string &, const Itinerary &);
    bool check_user_is_customer(const User &);
    std::vector<Itinerary> getCustomerItineraries(const std::string &);
    json getObjectsWithAttribute(const std::string &, const std::string &, const std::string &);
};
