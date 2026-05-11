#pragma once

#include "../model/user.hpp"

class AuthService;
class IOutput;
class IInput;

class LoginHandler
{
    AuthService &m_authService;
    IOutput &m_output;
    IInput &m_input;

public:
    LoginHandler(AuthService &authService, IOutput &output, IInput &input);
    [[nodiscard]] User login();
};
