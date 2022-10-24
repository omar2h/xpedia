#include "paymentCard.h"
#include <sstream>
std::string PaymentCard::toString() const
{
    std::stringstream oss;
    oss << "Owner: " << owner << "\n";
    oss << "Number: " << number << "\n";
    oss << "Expiry Date: " << expiryDate << "\n";
    return oss.str();
}
