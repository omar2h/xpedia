#include "user_repository.hpp"
#include "../exception.hpp"
#include "../infrastructure/json_keys.hpp"
#include "id_generator.hpp"
#include "storage/file_storage.hpp"

UserRepository::UserRepository(FileStorage &storage) : m_storage(storage) {}

void UserRepository::validateUserSignIn(const User &u)
{
    std::vector<std::string> emails{};
    std::vector<std::string> phones{};

    emails = m_storage.readJsonAttributeFromFile("users.json", JsonKeys::email);
    phones = m_storage.readJsonAttributeFromFile("users.json", JsonKeys::phone);

    auto it1 = find(emails.begin(), emails.end(), u.getEmail());
    auto it2 = find(phones.begin(), phones.end(), u.getPhone());

    if (it1 != emails.end() || it2 != phones.end())
    {
        throw ValidationException("Email/Phone already in use");
    }
}

std::string UserRepository::generateUserId()
{
    std::string newId = generateId();
    return newId;
}

json convertUserToJson(const User &user)
{
    json obj;
    obj[JsonKeys::id] = user.getId();
    obj[JsonKeys::firstName] = user.getFirstName();
    obj[JsonKeys::lastName] = user.getLastName();
    obj[JsonKeys::email] = user.getEmail();
    obj[JsonKeys::phone] = user.getPhone();
    obj[JsonKeys::password] = user.getPassword();
    return obj;
}

std::vector<User> getUsersFromObjects(json arr)
{
    std::vector<User> data{};
    for (const auto &u : arr)
    {
        std::string firstName = u.value(JsonKeys::firstName, "not found");
        std::string lastName = u.value(JsonKeys::lastName, "not found");
        std::string email = u.value(JsonKeys::email, "not found");
        std::string phone = u.value(JsonKeys::phone, "not found");
        std::string password = u.value(JsonKeys::password, "not found");
        std::string id = u.value(JsonKeys::id, "not found");
        User tmp{id, firstName, lastName, email, phone, password};
        data.push_back(tmp);
    }
    return data;
}
