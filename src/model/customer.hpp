#pragma once

#include "user.hpp"
#include "payment_card.hpp"
#include <vector>
class Customer : public User
{
    std::vector<PaymentCard> cards{};
    std::vector<std::string> itineraryIds{};

public:
    Customer() = default;
    Customer(const User &);
    void addCard(const PaymentCard &);
    void addItineraryId(const std::string &);
    std::vector<PaymentCard> getCards() const { return cards; }
    void setCards(const std::vector<PaymentCard> &cards_) { cards = cards_; }
    std::vector<std::string> getItinerariesIds() const { return itineraryIds; }
};
