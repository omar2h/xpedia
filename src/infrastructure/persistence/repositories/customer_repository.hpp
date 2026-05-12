#pragma once

#include "../../../domain/entities/customer.hpp"
#include "../../../third_party/json.hpp"
using json = nlohmann::json;

class FileStorage;

class CustomerRepository
{
    FileStorage &m_storage;

public:
    explicit CustomerRepository(FileStorage &storage);

    [[nodiscard]] Customer getCustomer(const User &) const;

    void updateCustomer(const Customer &) const;

    [[nodiscard]] json convertCardToJson(const PaymentCard &) const;

    [[nodiscard]] json convertCustomerToJson(const Customer &) const;

    [[nodiscard]] bool customerExists(const std::string &) const;
};
