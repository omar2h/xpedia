#pragma once

#include "user_repository.hpp"
#include "customer_repository.hpp"
#include "../model/customer.hpp"
#include "../model/itinerary.hpp"
#include "repositories/itinerary_repository.hpp"
#include "storage/file_storage.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class Database
{
    UserRepository userRepository;
    CustomerRepository customerRepository;
    FileStorage storage{};
    ItineraryRepository itineraryRepository;

public:
    Database();

    std::unordered_set<std::string> get_users_ids();
    void save_user(User &);
    std::vector<std::string> read_file(const std::string &);
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
    json get_arr_objects_with_att(const std::string &, const std::string &, const std::string &);
};
