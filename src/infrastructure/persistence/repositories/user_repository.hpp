#pragma once

#include "../../../domain/entities/user.hpp"
#include "../../../third_party/json.hpp"
#include <unordered_set>
#include <string>
using json = nlohmann::json;

class FileStorage;

class UserRepository
{
    FileStorage &m_storage;

public:
    explicit UserRepository(FileStorage &storage);

    void validateUserSignIn(const User &);
    [[nodiscard]] std::string generateUserId();
};

[[nodiscard]] json convertUserToJson(const User &);
[[nodiscard]] std::vector<User> getUsersFromObjects(json);

