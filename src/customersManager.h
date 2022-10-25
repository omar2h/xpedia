#ifndef __CUSTOMERSMANAGER_H__
#define __CUSTOMERSMANAGER_H__
#include "customer.h"
#include "include/json.hpp"
using json = nlohmann::json;

class CustomersManager
{
public:
    Customer getCustomer(const User &) const;

    void update_customer(const Customer &) const;

    json convert_card_to_json(const PaymentCard &) const;

    json convert_customer_to_json(const Customer &) const;
};
#endif // __CUSTOMERSMANAGER_H__