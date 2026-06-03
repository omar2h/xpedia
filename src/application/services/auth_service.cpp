#include "auth_service.hpp"
#include "../../domain/validators/email_validator.hpp"
#include "../../domain/validators/password_validator.hpp"
#include "../../exception.hpp"
#include "../../util/password_utils.hpp"
#include "../repositories/i_user_repository.hpp"

AuthService::AuthService(IUserRepository& userRepo) : m_userRepo(userRepo) {}

void AuthService::signup(User& user)
{
    const auto& email = user.getEmail();
    const auto& password = user.getPassword();

    if (!EmailValidator::isValid(email))
        throw ValidationException(EmailValidator::getError(email));

    if (!PasswordValidator::isValid(password))
        throw ValidationException(PasswordValidator::getError(password));

    std::string hashedPassword = PasswordUtils::hashPassword(password);
    user.setPassword(hashedPassword);

    m_userRepo.saveUser(user);
}

User AuthService::login(const std::string& email, const std::string& password)
{
    if (email.empty() || password.empty())
        throw AuthException("Email and password are required");

    auto user = m_userRepo.findByUsername(email);

    if (user && PasswordUtils::verifyPassword(password, user->getPassword()))
        return *user;

    throw AuthException("Invalid email/password");
}
