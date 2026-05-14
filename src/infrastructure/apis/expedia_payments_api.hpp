#pragma once

#include <string>

class PayPalCreditCard
{
public:
	std::string name;
	std::string address;
	std::string id;
	std::string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI
{
public:
	void SetCardInfo(const PayPalCreditCard *const card) const
	{
	}
	bool MakePayment(double money) const
	{
		return true;
	}
};

class StripeUserInfo
{
public:
	std::string name;
	std::string address;
};

class StripeCardInfo
{
public:
	std::string id;
	std::string expiry_date;
};

class StripePaymentAPI
{
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money)
	{
		return true;
	}
};

class SquarePaymentAPI
{
public:
	bool static WithDrawMoney(std::string JsonQuery)
	{
		return true;
	}
};
