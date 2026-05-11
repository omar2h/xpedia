#pragma once

class IFrontend;
class Application;

class App
{
    IFrontend &m_frontend;
    Application &m_backend;

public:
    App(IFrontend &frontend, Application &backend);
    void run();
};