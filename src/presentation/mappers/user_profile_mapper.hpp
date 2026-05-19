#pragma once

#include "../view_models/view_models.hpp"
#include "../../domain/entities/user.hpp"

inline UserProfileViewModel toUserProfileViewModel(const User& user)
{
    return {user.getFirstName() + " " + user.getLastName(),
            user.getEmail(),
            user.getPhone()};
}
