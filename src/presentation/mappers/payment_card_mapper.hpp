#pragma once

#include "../formatters/reservation_formatter.hpp"
#include "../view_models/view_models.hpp"

inline PaymentCardViewModel toPaymentCardViewModel(const PaymentCard& card)
{
    return {formatPaymentCard(card)};
}
