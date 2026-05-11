#pragma once

#include "../model/user.hpp"

class Application;

class LoginHandler
{
    Application &m_backend;

public:
    explicit LoginHandler(Application &backend);
    User login();
};
