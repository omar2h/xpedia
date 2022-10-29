#ifndef __USERSMANAGER_H__
#define __USERSMANAGER_H__
#include "../model/user.h"
#include "../include/json.hpp"
#include <unordered_set>
#include <string>
using json = nlohmann::json;

class UsersManager
{
    static std::unordered_set<std::string> usersIds;

public:
    static void validate_user_sign_in(const User &);
    static std::string generate_user_id();
    json convert_user_to_json(const User &) const;
    static std::vector<User> get_users_from_objects(json);
};
#endif // __USERSMANAGER_H__