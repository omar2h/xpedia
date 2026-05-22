#include "auth_module.hpp"

#include <memory>

#include "application/services/auth_service.hpp"

#include "presentation/presenters/auth_presenter.hpp"

#include "presentation/view/view_interface.hpp"
#include "presentation/input.hpp"

#include "application/repositories/i_user_repository.hpp"

AuthModule createAuthModule(IView &view, IInput &input, IUserRepository &userRepo)
{
    AuthModule module;
    module.authService = std::make_unique<AuthService>(userRepo);
    module.presenter = std::make_unique<AuthPresenter>(view, input, *module.authService);

    return module;
}