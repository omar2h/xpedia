#pragma once

#include "../model/user.hpp"
#include "../model/customer.hpp"
#include "../model/itinerary.hpp"
#include <string>
#include <vector>

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual void saveUser(User &) = 0;
    [[nodiscard]] virtual std::vector<User> getUsers(const std::string &) const = 0;
    [[nodiscard]] virtual Customer getCustomer(const User &) = 0;
    virtual void updateCustomerInfo(const Customer &) = 0;
    virtual void saveItinerary(const std::string &, const Itinerary &) = 0;
    [[nodiscard]] virtual bool checkUserIsCustomer(const User &) = 0;
    [[nodiscard]] virtual std::vector<Itinerary> getCustomerItineraries(const std::string &) = 0;
};
