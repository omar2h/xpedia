#ifndef __CUSTOMERSMANAGER_H__
#define __CUSTOMERSMANAGER_H__
#include "customer.h"

class CustomersManager
{
public:
    Customer getCustomer(const User &);
};
#endif // __CUSTOMERSMANAGER_H__