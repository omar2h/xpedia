#include "user_repository.hpp"
#include "id_generator.hpp"
#include "storage/file_storage.hpp"
#include <iostream>
std::unordered_set<std::string> UserRepository::usersIds{};

UserRepository::UserRepository(FileStorage &storage) : m_storage(storage) {}

void UserRepository::validate_user_sign_in(const User &u)
{
    std::vector<std::string> emails{};
    std::vector<std::string> phones{};

    emails = m_storage.read_json_attribute_from_file("users.json", "email");
    phones = m_storage.read_json_attribute_from_file("users.json", "phone");

    auto it1 = find(emails.begin(), emails.end(), u.getEmail());
    auto it2 = find(phones.begin(), phones.end(), u.getPhone());

    if (it1 != emails.end() || it2 != phones.end())
    {
        throw std::runtime_error("Email/Phone already in use");
    }
}

std::string UserRepository::generate_user_id()
{
    std::string newId = IdGenerator::generate_id(usersIds);
    usersIds.insert(newId);
    return newId;
}

json UserRepository::convert_user_to_json(const User &user)
{
    json obj;
    obj["id"] = user.getId();
    obj["firstName"] = user.getFirstName();
    obj["lastName"] = user.getLastName();
    obj["email"] = user.getEmail();
    obj["phone"] = user.getPhone();
    obj["password"] = user.getPassword();
    return obj;
}

std::vector<User> UserRepository::get_users_from_objects(json arr)
{
    std::vector<User> data{};
    for (const auto &u : arr)
    {
        std::string firstName = u.value("firstName", "not found");
        std::string lastName = u.value("lastName", "not found");
        std::string email = u.value("email", "not found");
        std::string phone = u.value("phone", "not found");
        std::string password = u.value("password", "not found");
        std::string id = u.value("id", "not found");
        User tmp{id, firstName, lastName, email, phone, password};
        data.push_back(tmp);
    }
    return data;
}
