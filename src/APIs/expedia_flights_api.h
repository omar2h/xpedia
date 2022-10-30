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

class BritishAirwaysCustomerInfo
{
};

class BritishAirwaysFlight
{
public:
	double price;
	string date;
};

class BritishAirwaysOnlineAPI
{
public:
	static vector<BritishAirwaysFlight> GetFlights(string const &from, string const &date, string const &to, int adults, int childern)
	{
		vector<BritishAirwaysFlight> flights;

		flights.push_back({200, "25-01-2022"});
		flights.push_back({250, "29-01-2022"});
		return flights;
	}
	static bool ReserveFlight(const BritishAirwaysFlight &flight, const BritishAirwaysCustomerInfo &info)
	{
		return true;
	}
};

class AirFranceFlight
{
public:
	double cost;
	string date;
};

class AirFranceCustomerInfo
{
};

class AirFranceOnlineAPI
{
public:
	void SetInfo(string const &date, string const &from, string const &to)
	{
	}
	void SetPassengersInfo(int childern, int adults)
	{
	}
	vector<AirFranceFlight> GetAvailableFlights() const
	{
		vector<AirFranceFlight> flights;

		flights.push_back({300, "10-01-2022"});
		flights.push_back({320, "12-01-2022"});
		return flights;
	}

	static bool ReserveFlight(const AirFranceCustomerInfo &info, const AirFranceFlight &flight)
	{
		return false;
	}
};

#endif /* EXPEDIA_FLIGHTS_API_H_ */
