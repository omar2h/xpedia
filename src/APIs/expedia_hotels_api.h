/*
 * expedia_hotels_api.h
 *
 *  Created on: Sep 22, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_HOTELS_API_H_
#define EXPEDIA_HOTELS_API_H_

#include <string>
#include <vector>

using namespace std;

class HiltonRoom
{
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI
{
public:
	static vector<HiltonRoom> SearchRooms(string city, string from_date, string to_date, int adults, int children, int needed_rooms)
	{
		vector<HiltonRoom> rooms;

		rooms.push_back({"Interior View", 6, 200.0, "01-05-2023", "10-05-2023"});
		rooms.push_back({"City View", 3, 300.0, "01-05-2023", "10-05-2023"});
		rooms.push_back({"Deluxe View", 8, 500.0, "01-05-2023", "10-05-2023"});

		return rooms;
	}

	static bool reserve()
	{
		return true;
	}
};

class MarriottFoundRoom
{
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI
{
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string city, int needed_rooms, int adults, int children)
	{
		vector<MarriottFoundRoom> rooms;

		rooms.push_back({"City View", 8, 320.0, "01-05-2023", "10-05-2023"});
		rooms.push_back({"Interior View", 8, 220.0, "01-05-2023", "10-05-2023"});
		rooms.push_back({"Private View", 5, 600.0, "01-05-2023", "10-05-2023"});

		return rooms;
	}
	static bool reserve()
	{
		return true;
	}
};

#endif /* EXPEDIA_HOTELS_API_H_ */
