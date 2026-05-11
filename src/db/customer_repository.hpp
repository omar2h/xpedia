#pragma once

#include "../model/customer.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

class FileStorage;

class CustomerRepository
{
    FileStorage &m_storage;

public:
    explicit CustomerRepository(FileStorage &storage);

    Customer getCustomer(const User &) const;

    void update_customer(const Customer &) const;

    json convert_card_to_json(const PaymentCard &) const;

    json convert_customer_to_json(const Customer &) const;

    bool check_if_customer_exists(const std::string &) const;
};
