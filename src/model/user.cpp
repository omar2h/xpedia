#include "user.h"

User::User()
{
}

User::User(const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &phone,
           const std::string &password) : firstName(firstName), lastName(lastName), email(email), phone(phone), password(password)
{
}

User::User(const std::string &id, const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &phone,
           const std::string &password) : id(id), firstName(firstName), lastName(lastName), email(email), phone(phone), password(password)
{
}
