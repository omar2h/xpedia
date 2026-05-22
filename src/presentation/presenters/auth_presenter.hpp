#pragma once

#include <optional>

#include "../app_state.hpp"

class IView;
class IInput;
class AuthService;

class AuthPresenter
{
    IView &m_view;
    IInput &m_input;
    AuthService &m_authService;

public:
    AuthPresenter(IView &view, IInput &input, AuthService &authService);

    AuthResult run();

private:
    [[nodiscard]] User login();
    void signup();
};