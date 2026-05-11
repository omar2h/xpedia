#pragma once

class IFrontend;
class Backend;

class App
{
    IFrontend &m_frontend;
    Backend &m_backend;

public:
    App(IFrontend &frontend, Backend &backend);
    void run();
};