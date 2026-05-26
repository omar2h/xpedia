#pragma once

#include "user.hpp"
#include "payment_card.hpp"
#include <vector>
class Customer : public User
{
    std::vector<PaymentCard> cards{};
    std::vector<std::string> itineraryIds{};
    PaymentCard m_selectedCard{};

public:
    Customer() = default;
    Customer(const User &);
    void addCard(const PaymentCard &);
    void addItineraryId(const std::string &);
    [[nodiscard]] const std::vector<PaymentCard> &getCards() const { return cards; }
    void setCards(const std::vector<PaymentCard> &cards_) { cards = cards_; }
    [[nodiscard]] const std::vector<std::string> &getItinerariesIds() const { return itineraryIds; }
    void setSelectedCard(const PaymentCard& card) { m_selectedCard = card; }
    [[nodiscard]] const PaymentCard& getSelectedCard() const { return m_selectedCard; }
};
