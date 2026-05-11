#pragma once

class Application;

class SignupHandler
{
    Application &m_application;

public:
    explicit SignupHandler(Application &backend);
    void signup();
};
