#pragma once

#include "../model/user.hpp"
#include "../third_party/json.hpp"
#include <unordered_set>
#include <string>
using json = nlohmann::json;

class FileStorage;

class UserRepository
{
    FileStorage &m_storage;
    std::unordered_set<std::string> usersIds;

public:
    explicit UserRepository(FileStorage &storage);

    void validateUserSignIn(const User &);
    [[nodiscard]] std::string generateUserId();
};

[[nodiscard]] json convertUserToJson(const User &);
[[nodiscard]] std::vector<User> getUsersFromObjects(json);

