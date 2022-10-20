#include "backEnd.h"
#include "database.h"

void BackEnd::save_user_in_db(User &user)
{
    try
    {
        Database::get_database()->save_user(user);
    }
    catch (int e)
    {
        throw e;
    }
}

User BackEnd::user_login(const std::string &email, const std::string &password)
{
    std::vector<User> users{};
    users = Database::get_database()->get_users(USERS_JSON);

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }
    throw 5;
}
