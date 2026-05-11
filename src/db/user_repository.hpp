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
    static std::unordered_set<std::string> usersIds;

public:
    explicit UserRepository(FileStorage &storage);

    void validateUserSignIn(const User &);
    static std::string generateUserId();
    static json convert_user_to_json(const User &);
    static std::vector<User> get_users_from_objects(json);
};
