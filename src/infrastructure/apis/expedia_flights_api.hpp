#pragma once
#include <string>
#include <vector>

class BritishAirwaysCustomerInfo
{
};

class BritishAirwaysFlight
{
public:
	double price;
	std::string date;
};

class BritishAirwaysOnlineAPI
{
public:
	static std::vector<BritishAirwaysFlight> GetFlights(std::string const &from, std::string const &date, std::string const &to, int adults, int childern)
	{
		std::vector<BritishAirwaysFlight> flights;

		flights.push_back({200, "01-05-2023"});
		flights.push_back({250, "01-05-2023"});
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
	std::string date;
};

class AirFranceCustomerInfo
{
};

class AirFranceOnlineAPI
{
public:
	void SetInfo(std::string const &date, std::string const &from, std::string const &to)
	{
	}
	void SetPassengersInfo(int childern, int adults)
	{
	}
	std::vector<AirFranceFlight> GetAvailableFlights() const
	{
		std::vector<AirFranceFlight> flights;

		flights.push_back({300, "01-05-2023"});
		flights.push_back({320, "01-05-2023"});
		return flights;
	}

	static bool ReserveFlight(const AirFranceCustomerInfo &info, const AirFranceFlight &flight)
	{
		return false;
	}
};
