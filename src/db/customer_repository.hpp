#pragma once

#include "../model/customer.hpp"
#include "../third_party/json.hpp"
using json = nlohmann::json;

class FileStorage;

class CustomerRepository
{
    FileStorage &m_storage;

public:
    explicit CustomerRepository(FileStorage &storage);

    Customer getCustomer(const User &) const;

    void updateCustomer(const Customer &) const;

    json convert_card_to_json(const PaymentCard &) const;

    json convert_customer_to_json(const Customer &) const;

    bool customerExists(const std::string &) const;
};
