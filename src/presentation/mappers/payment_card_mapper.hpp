#pragma once

#include "../view_models/view_models.hpp"
#include "../formatters/reservation_formatter.hpp"

inline PaymentCardViewModel toPaymentCardViewModel(const PaymentCard& card)
{
    return {formatPaymentCard(card)};
}
