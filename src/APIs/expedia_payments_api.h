/*
 * expedia_payments_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_PAYMENTS_API_H_
#define EXPEDIA_PAYMENTS_API_H_
#include <string>
using namespace std;

class PayPalCreditCard
{
public:
	string name;
	string address;
	string id;
	string expiry_date;
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
	string name;
	string address;
};

class StripeCardInfo
{
public:
	string id;
	string expiry_date;
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
	bool static WithDrawMoney(string JsonQuery)
	{
		// cout << JsonQuery << "\n";
		// json::JSON obj = JSON::Load(JsonQuery);
		return true;
	}
};

#endif /* EXPEDIA_PAYMENTS_API_H_ */
