#pragma once

#include "../../domain/entities/customer.hpp"
#include <optional>
#include <string>

class ICustomerRepository
{
  public:
    virtual ~ICustomerRepository() = default;

    [[nodiscard]] virtual std::optional<Customer> findById(const std::string& userId) const = 0;

    virtual void update(const Customer&) = 0;
};
