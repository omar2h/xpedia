#include "database.h"
#include "error.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

std::unique_ptr<Database> Database::databaseInstance = nullptr;

std::unique_ptr<Database> Database::get_database()
{
    if (databaseInstance == nullptr)
        databaseInstance = std::unique_ptr<Database>{};
    return std::move(databaseInstance);
}

json Database::get_objects_from_file(const std::string &path) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw 3;
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
        throw 4;
    file_handler.close();

    return arr;
}

void Database::delete_object_with_id(const std::string &path, const std::string &id)
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw 3;
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
        throw 4;
    file_handler.close();

    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i].value("id", "not found") << "\n";
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
    if (!exist)
        return false;
    return true;
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
        throw 3;
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
        throw 4;
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
        throw 3;
    }

    file_handler << arr;
    file_handler.close();
}

json Database::get_object_with_id(const std::string &path, const std::string &id) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw 3;
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
        throw 4;
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
        throw 3;
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
    json arr = get_objects_from_file(path);
    return UsersManager::get_users_from_objects(arr);
}

Customer Database::getCustomer(const User &user)
{
    return customersManager.getCustomer(user);
}

void Database::update_customer_info(const Customer &customer)
{
    return customersManager.update_customer(customer);
}

std::vector<std::string> Database::read_json_attribute_from_file(const std::string &path, const std::string &att) const
{
    std::fstream file_handler(path.c_str());
    if (file_handler.fail())
    {
        throw 3;
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
    try
    {
        UsersManager::validate_user_sign_in(user);
    }
    catch (int e)
    {
        throw e;
    }
    std::string newId = UsersManager::generate_user_id();
    user.setId(newId);
    json obj = usersManager.convert_user_to_json(user);
    write_json_to_file(USERS_JSON, obj);
}

// std::vector<User> get_users_from_file(const std::string &path)
// {
//     std::fstream file_handler(path.c_str());
//     if (file_handler.fail())
//     {
//         throw 3;
//     }

//     json arr;
//     /* check if file is not empty */
//     file_handler.seekg(0, std::ios::end);
//     if (file_handler.tellg() != 0)
//     {
//         /* return the cursor to the beginning of the file */
//         file_handler.seekg(0, std::ios::beg);
//         arr = json::parse(file_handler);
//     }
//     else
//         throw 4;
//     file_handler.close();

//     std::vector<User> data{};
//     for (const auto &u : arr)
//     {
//         std::string firstName = u.value("firstName", "not found");
//         std::string lastName = u.value("lastName", "not found");
//         std::string email = u.value("email", "not found");
//         std::string phone = u.value("phone", "not found");
//         std::string password = u.value("password", "not found");
//         std::string id = u.value("id", "not found");
//         User tmp{id, firstName, lastName, email, phone, password};
//         data.push_back(tmp);
//     }
//     return data;
// }

// std::unordered_set<std::string> Database::get_users_ids()
// {
//     return usersIds;
// }

// std::vector<std::string> Database::read_file(const std::string& path)
// {
//     std::fstream file_handler(path.c_str());
//     if (file_handler.fail())
//     {
//         throw 5;
//     }

//     std::string line;
//     /* check if file is empty */
//     if (file_handler.peek() == std::ifstream::traits_type::eof())
//     {
//         file_handler.close();
//         return;
//     }

//     while (getline(file_handler, line))
//     {
//         if (line.size() == 0)
//             continue;
//         lines.push_back(line);
//     }

//     file_handler.close();
// }

// void Database::write_file_lines(const std::string &path, const std::vector<std::string> &lines, bool append = true) const
// {
//     auto status = std::ios::in | std::ios::out | std::ios::app;

//     if (!append)
//         status = std::ios::in | std::ios::out | std::ios::trunc; // overwrite

//     std::fstream file_handler(path.c_str(), status);

//     if (file_handler.fail())
//     {
//         throw 5;
//     }
//     for (const auto &line : lines)
//         file_handler << line << "\n";

//     file_handler.close();
// }