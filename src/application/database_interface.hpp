#pragma once

#include "../domain/entities/user.hpp"
#include "../domain/entities/customer.hpp"
#include "../domain/entities/itinerary.hpp"
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
