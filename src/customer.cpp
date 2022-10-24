#include "customer.h"
Customer::Customer(const User &user)
    : User(user)
{
}
void Customer::addCard(const PaymentCard &card)
{
    cards.push_back(card);
}

void Customer::addItineraryId(const std::string &id)
{
    itineraryIds.push_back(id);
}
