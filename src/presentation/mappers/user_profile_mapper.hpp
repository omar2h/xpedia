#pragma once

#include "../../domain/entities/user.hpp"
#include "../view_models/view_models.hpp"

inline UserProfileViewModel toUserProfileViewModel(const User& user)
{
    return {user.getFirstName() + " " + user.getLastName(), user.getEmail(), user.getPhone()};
}
