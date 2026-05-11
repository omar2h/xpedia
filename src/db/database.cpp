#include "database.hpp"
#include <fstream>
#include <vector>
#include <cstdio>

Database::Database()
    : userRepository(storage), customerRepository(storage), itineraryRepository(storage)
{
}

json Database::getObjectsFromFile(const std::string &path) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    else
        throw std::runtime_error("Invalid email/password(empty)"); // empty file
    file_handler.close();

    return arr;
}

void Database::deleteObjectWithId(const std::string &path, const std::string &id)
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    else
        throw std::runtime_error("No Reservations to Pay"); // empty file
    file_handler.close();

    for (int i = 0; i < (int)arr.size(); i++)
    {
        if (arr[i].value("id", "not found") == id)
        {
            arr.erase(i);
            break;
        }
    }
    writeJsonArrayToFile(path, arr, false);
}

void Database::saveItinerary(const std::string &customerId, const Itinerary &itinerary)
{
    itineraryRepository.save(customerId, itinerary);
}

bool Database::checkUserIsCustomer(const User &user)
{
    bool exist = customerRepository.customerExists(user.getId());

    return exist;
}

std::vector<Itinerary> Database::getCustomerItineraries(const std::string &customerId)
{
    return itineraryRepository.findByCustomerId(customerId);
}

json Database::getObjectsWithAttribute(const std::string &path, const std::string &attribute, const std::string &value)
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    else
        throw std::runtime_error("Invalid email/password(empty)"); // empty file
    file_handler.close();
    json objectsArr;
    for (const auto &u : arr)
    {
        if (u.value(attribute, "not found") == value)
            objectsArr.push_back(u);
    }
    return objectsArr;
}

void Database::writeJsonArrayToFile(const std::string &path, json arr, bool append = false)
{
    auto status = std::ios::in | std::ios::out | std::ios::app;

    if (!append)
        status = std::ios::in | std::ios::out | std::ios::trunc; // overwrite

    std::fstream file_handler(path.c_str(), status);

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    file_handler << arr;
    file_handler.close();
}

json Database::getObjectWithId(const std::string &path, const std::string &id) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    else
        throw std::runtime_error("Invalid email/password(empty)"); // empty file
    file_handler.close();

    for (const auto &u : arr)
    {
        if (u.value("id", "not found") == id)
            return u;
    }
    json obj;
    return obj;
}

void Database::writeJsonToFile(const std::string &path, json obj, bool append = true)
{
    auto status = std::ios::in | std::ios::out | std::ios::app;

    if (!append)
        status = std::ios::in | std::ios::out | std::ios::trunc; // overwrite

    std::fstream file_handler(path.c_str(), status);

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    nlohmann::json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    arr.push_back(obj);
    file_handler.close();

    remove(path.c_str());
    std::fstream f(path.c_str(), status);
    f << arr;
    f.close();
}

std::vector<User> Database::getUsers(const std::string &path) const
{
    json arr;
    arr = getObjectsFromFile(path);
    return UserRepository::getUsersFromObjects(arr);
}

Customer Database::getCustomer(const User &user)
{
    return customerRepository.getCustomer(user);
}

void Database::updateCustomerInfo(const Customer &customer)
{
    customerRepository.updateCustomer(customer);
}

std::vector<std::string> Database::readJsonAttributeFromFile(const std::string &path, const std::string &attribute) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file"); // failed to open file
    }

    json arr;
    /* check if file is not empty */
    file_handler.seekg(0, std::ios::end);
    if (file_handler.tellg() != 0)
    {
        /* return the cursor to the beginning of the file */
        file_handler.seekg(0, std::ios::beg);
        arr = json::parse(file_handler);
    }
    file_handler.close();

    std::vector<std::string> data{};
    for (const auto &u : arr)
    {
        data.push_back(u.value(attribute, "not found"));
    }
    return data;
}

void Database::saveUser(User &user)
{
    userRepository.validateUserSignIn(user);
    std::string newId = UserRepository::generateUserId();
    user.setId(newId);
    json obj = UserRepository::convertUserToJson(user);
    writeJsonToFile("users.json", obj);
}