#pragma once

class Application;
class IOutput;
class IInput;

class SignupHandler
{
    Application &m_application;
    IOutput &m_output;
    IInput &m_input;

public:
    SignupHandler(Application &backend, IOutput &output, IInput &input);
    void signup();
};
