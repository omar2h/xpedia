#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "usersManager.h"
#include "customersManager.h"
#include "../model/customer.h"
#include "../model/itinerary.h"
#include "itinerariesManager.h"
#include <string>
#include <memory>
#include <unordered_set>
#include <vector>

#define USERS_JSON "src/users.json"
#define CUSTOMERS_JSON "src/customers.json"
#define ITINERARIES_JSON "src/itineraries.json"
class Database
{
    static std::unique_ptr<Database> databaseInstance;
    Database() = default;
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

    UsersManager usersManager{};
    CustomersManager customersManager{};
    ItinerariesManager itinerariesManger{};

public:
    static std::unique_ptr<Database> get_database();
    std::unordered_set<std::string> get_users_ids();
    void save_user(User &) const;
    std::vector<std::string> read_file(const std::string &);
    json get_objects_from_file(const std::string &) const;
    json get_object_with_id(const std::string &, const std::string &) const;
    std::vector<std::string> read_json_attribute_from_file(const std::string &, const std::string &) const;
    void write_json_to_file(const std::string &, json, bool) const;
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
#endif // __DATABASE_H__
