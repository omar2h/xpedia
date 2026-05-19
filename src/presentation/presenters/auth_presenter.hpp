#pragma once

#include <optional>
#include "../app_state.hpp"

class IView;
class IInput;
class LoginHandler;
class SignupHandler;

class AuthPresenter
{
    IView& m_view;
    IInput& m_input;
    LoginHandler& m_loginHandler;
    SignupHandler& m_signupHandler;

public:
    AuthPresenter(IView& view, IInput& input, LoginHandler& loginHandler, SignupHandler& signupHandler);
    AuthResult run();
};
