#pragma once

class Backend;

class SignupHandler
{
    Backend &m_backend;

public:
    explicit SignupHandler(Backend &backend);
    void signup();
};
