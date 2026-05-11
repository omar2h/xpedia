#pragma once

class AuthService;
class IOutput;
class IInput;

class SignupHandler
{
    AuthService &m_authService;
    IOutput &m_output;
    IInput &m_input;

public:
    SignupHandler(AuthService &authService, IOutput &output, IInput &input);
    void signup();
};
