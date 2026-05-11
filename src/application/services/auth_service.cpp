#include "auth_service.hpp"
#include "../../exception.hpp"
#include "../database_interface.hpp"

AuthService::AuthService(IDatabase &database)
    : m_database(database) {}

void AuthService::signup(User &user)
{
    const auto &email = user.getEmail();
    const auto &password = user.getPassword();

    if (email.find('@') == std::string::npos || email.find('.') == std::string::npos)
        throw ValidationException("Invalid email format");

    if (password.size() < 4)
        throw ValidationException("Password must be at least 4 characters");

    m_database.saveUser(user);
}

User AuthService::login(const std::string &email, const std::string &password)
{
    if (email.empty() || password.empty())
        throw AuthException("Email and password are required");

    std::vector<User> users = m_database.getUsers("users.json");

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }

    throw AuthException("Invalid email/password");
}
