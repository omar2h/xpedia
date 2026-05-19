#pragma once

#include "../../domain/entities/user.hpp"
#include <optional>
#include <string>

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    virtual void saveUser(const User &) = 0;

    [[nodiscard]] virtual std::optional<User>
    findByUsername(const std::string &username) const = 0;
};
