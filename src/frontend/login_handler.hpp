#pragma once

#include "../model/user.hpp"

class Application;

class LoginHandler
{
    Application &m_application;

public:
    explicit LoginHandler(Application &backend);
    [[nodiscard]] User login();
};
