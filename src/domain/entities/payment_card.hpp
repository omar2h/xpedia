#pragma once

#include <string>

class PaymentCard
{
    std::string number{};
    std::string owner{};
    std::string expiryDate{};
    std::string ccv{};

  public:
    PaymentCard() = default;
    PaymentCard(const std::string& number, const std::string& owner, const std::string& date, const std::string& ccv)
        : number{number}, owner{owner}, expiryDate{date}, ccv{ccv}
    {
    }

    [[nodiscard]] const std::string& getOwner() const
    {
        return owner;
    }
    void setOwner(const std::string& owner_)
    {
        owner = owner_;
    }

    [[nodiscard]] const std::string& getNumber() const
    {
        return number;
    }
    void setNumber(const std::string& number_)
    {
        number = number_;
    }

    [[nodiscard]] const std::string& getExpiryDate() const
    {
        return expiryDate;
    }
    void setExpiryDate(const std::string& expiryDate_)
    {
        expiryDate = expiryDate_;
    }

    [[nodiscard]] const std::string& getCcv() const
    {
        return ccv;
    }
    void setCcv(const std::string& ccv_)
    {
        ccv = ccv_;
    }
};
