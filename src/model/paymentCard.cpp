#include "paymentCard.h"
#include <sstream>
std::string PaymentCard::toString() const
{
    std::stringstream oss;
    oss << "Number: " << number << ", "
        << "Owner: " << owner << "Expiry Date: " << expiryDate;
    return oss.str();
}
