#pragma once

#include "../../domain/entities/user.hpp"
#include <string>

class IDatabase;

class AuthService
{
    IDatabase &m_database;

public:
    AuthService(IDatabase &database);

    void signup(User &user);
    [[nodiscard]] User login(const std::string &email, const std::string &password);
};
