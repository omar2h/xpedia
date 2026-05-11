#pragma once

#include "../model/user.hpp"

class Application;
class IOutput;
class IInput;

class LoginHandler
{
    Application &m_application;
    IOutput &m_output;
    IInput &m_input;

public:
    LoginHandler(Application &backend, IOutput &output, IInput &input);
    [[nodiscard]] User login();
};
