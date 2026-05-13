#include "database.hpp"

Database::Database()
    : userRepository(storage), customerRepository(storage), itineraryRepository(storage)
{
}

void Database::saveItinerary(const std::string &customerId, const Itinerary &itinerary)
{
    itineraryRepository.save(customerId, itinerary);
}

bool Database::checkUserIsCustomer(const User &user)
{
    return customerRepository.customerExists(user.getId());
}

std::vector<Itinerary> Database::getCustomerItineraries(const std::string &customerId)
{
    return itineraryRepository.findByCustomerId(customerId);
}

std::vector<User> Database::getUsers(const std::string &path) const
{
    json arr = storage.readAll(path);
    return getUsersFromObjects(arr);
}

Customer Database::getCustomer(const User &user)
{
    return customerRepository.getCustomer(user);
}

void Database::updateCustomerInfo(const Customer &customer)
{
    customerRepository.updateCustomer(customer);
}

void Database::saveUser(User &user)
{
    userRepository.validateUserSignIn(user);
    std::string newId = userRepository.generateUserId();
    user.setId(newId);
    json obj = convertUserToJson(user);
    storage.writeJsonToFile("users.json", obj, true);
}