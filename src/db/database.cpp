#include "database.hpp"
#include "../error.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

Database *Database::get_database()
{
    static Database databaseInstance{};
    return &databaseInstance;
}

json Database::get_objects_from_file(const std::string &path) const
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

void Database::delete_object_with_id(const std::string &path, const std::string &id)
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
        std::cout << "database line 64 " << arr[i].value("id", "not found") << "\n";
        if (arr[i].value("id", "not found") == id)
        {
            arr.erase(i);
            break;
        }
    }
    write_json_array_to_file(path, arr, false);
}

void Database::save_itinerary(const std::string &customerId, const Itinerary &itinerary)
{
    itinerariesManger.save_itinerary(customerId, itinerary);
}

bool Database::check_user_is_customer(const User &user)
{
    bool exist = customersManager.check_if_customer_exists(user.getId());

    return exist;
}

std::vector<Itinerary> Database::getCustomerItineraries(const std::string &customerId)
{
    return itinerariesManger.getItineraries_with_customerId(customerId);
}

json Database::get_arr_objects_with_att(const std::string &path, const std::string &jsonAtt, const std::string &att)
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
        if (u.value(jsonAtt, "not found") == att)
            objectsArr.push_back(u);
    }
    return objectsArr;
}

void Database::write_json_array_to_file(const std::string &path, json arr, bool append = false)
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

json Database::get_object_with_id(const std::string &path, const std::string &id) const
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

void Database::write_json_to_file(const std::string &path, json obj, bool append = true) const
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
        std::cout << arr.size() << "\n";
    }
    arr.push_back(obj);
    file_handler.close();

    remove(path.c_str());
    std::fstream f(path.c_str(), status);
    f << arr;
    f.close();
}

std::vector<User> Database::get_users(const std::string &path) const
{
    json arr;
    arr = get_objects_from_file(path);
    return UsersManager::get_users_from_objects(arr);
}

Customer Database::getCustomer(const User &user)
{
    return customersManager.getCustomer(user);
}

void Database::update_customer_info(const Customer &customer)
{
    customersManager.update_customer(customer);
}

std::vector<std::string> Database::read_json_attribute_from_file(const std::string &path, const std::string &att) const
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
        data.push_back(u.value(att, "not found"));
    }
    return data;
}

void Database::save_user(User &user) const
{
    UsersManager::validate_user_sign_in(user);
    std::string newId = UsersManager::generate_user_id();
    user.setId(newId);
    json obj = usersManager.convert_user_to_json(user);
    write_json_to_file(USERS_JSON, obj);
}