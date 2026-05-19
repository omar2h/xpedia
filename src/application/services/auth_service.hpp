#pragma once

#include "../../domain/entities/user.hpp"
#include <string>

class IUserRepository;

class AuthService
{
    IUserRepository &m_userRepo;

public:
    AuthService(IUserRepository &userRepo);

    void signup(User &user);
    [[nodiscard]] User login(const std::string &email, const std::string &password);
};
