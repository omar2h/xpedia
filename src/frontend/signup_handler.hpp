#pragma once

class Application;

class SignupHandler
{
    Application &m_backend;

public:
    explicit SignupHandler(Application &backend);
    void signup();
};
