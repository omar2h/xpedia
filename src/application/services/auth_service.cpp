#include "auth_service.hpp"
#include "../../exception.hpp"
#include "../database_interface.hpp"
#include "../../util/password_utils.hpp"
#include <algorithm>

AuthService::AuthService(IDatabase &database)
    : m_database(database) {}

void AuthService::signup(User &user)
{
    const auto &email = user.getEmail();
    const auto &password = user.getPassword();

    // Improved email validation
    if (email.find('@') == std::string::npos ||
        email.find('.') == std::string::npos ||
        email.find('@') > email.find('.'))
        throw ValidationException("Invalid email format");

    // Stronger password validation
    if (password.size() < 8)
        throw ValidationException("Password must be at least 8 characters");

    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;
    for (char c : password)
    {
        if (std::isdigit(c))
            hasDigit = true;
        if (std::isupper(c))
            hasUpper = true;
        if (std::islower(c))
            hasLower = true;
    }
    if (!hasDigit || !hasUpper || !hasLower)
        throw ValidationException("Password must contain at least one digit, one uppercase letter, and one lowercase letter");

    // Hash the password before storing
    std::string hashedPassword = PasswordUtils::hashPassword(password);
    user.setPassword(hashedPassword);

    m_database.saveUser(user);
}

User AuthService::login(const std::string &email, const std::string &password)
{
    if (email.empty() || password.empty())
        throw AuthException("Email and password are required");

    std::vector<User> users = m_database.getUsers("users.json");

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email)
        {
            // Verify password hash
            if (PasswordUtils::verifyPassword(password, usr.getPassword()))
                return usr;
        }
    }

    throw AuthException("Invalid email/password");
}
