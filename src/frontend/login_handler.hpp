#pragma once

#include "../model/user.hpp"

class Backend;

class LoginHandler
{
    Backend &m_backend;

public:
    explicit LoginHandler(Backend &backend);
    User login();
};
