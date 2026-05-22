// composition/auth/auth_module.hpp

#pragma once

#include <memory>

#include "application/services/auth_service.hpp"
#include "presentation/presenters/auth_presenter.hpp"

class IView;
class IInput;
class IUserRepository;

struct AuthModule
{
    std::unique_ptr<AuthService> authService;
    std::unique_ptr<AuthPresenter> presenter;
};

AuthModule createAuthModule(IView &view, IInput &input, IUserRepository &userRepo);
