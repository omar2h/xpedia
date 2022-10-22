/*
 * expedia_flights_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_FLIGHTS_API_H_
#define EXPEDIA_FLIGHTS_API_H_

#include <string>
#include <vector>

using namespace std;

class AirCanadaCustomerInfo
{
};

class AirCanadaFlight
{
public:
	double price;
	string date;
};

class AirCanadaOnlineAPI
{
public:
	static vector<AirCanadaFlight> GetFlights(string const &from, string const &date, string const &to, int adults, int childern)
	{
		vector<AirCanadaFlight> flights;

		flights.push_back({200, "25-01-2022"});
		flights.push_back({250, "29-01-2022"});
		return flights;
	}
	static bool ReserveFlight(const AirCanadaFlight &flight, const AirCanadaCustomerInfo &info)
	{
		return true;
	}
};

class TurkishFlight
{
public:
	double cost;
	string date;
};

class TurkishCustomerInfo
{
};

class TurkishAirlinesOnlineAPI
{
public:
	void SetInfo(string const &date, string const &from, string const &to)
	{
	}
	void SetPassengersInfo(int childern, int adults)
	{
	}
	vector<TurkishFlight> GetAvailableFlights() const
	{
		vector<TurkishFlight> flights;

		flights.push_back({300, "10-01-2022"});
		flights.push_back({320, "12-01-2022"});
		return flights;
	}

	static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight &flight)
	{
		return false;
	}
};

#endif /* EXPEDIA_FLIGHTS_API_H_ */
