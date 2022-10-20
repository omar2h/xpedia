#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "usersManager.h"
#include <string>
#include <memory>
#include <unordered_set>
#include <vector>

#define USERS_JSON "users.json"
class Database
{
    static std::unique_ptr<Database> databaseInstance;
    Database() = default;
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

    UsersManager usersManager{};

public:
    static std::unique_ptr<Database> get_database();
    std::unordered_set<std::string> get_users_ids();
    void save_user(User &) const;
    std::vector<std::string> read_file(const std::string &);
    json get_objects_from_file(const std::string &) const;
    std::vector<std::string> read_json_attribute_from_file(const std::string &, const std::string &) const;
    void write_json_to_file(const std::string &, json, bool) const;
    std::vector<User> get_users(const std::string &) const;
};
#endif // __DATABASE_H__