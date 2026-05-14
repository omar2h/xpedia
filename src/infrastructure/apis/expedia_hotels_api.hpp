#pragma once
#include <string>
#include <vector>

class HiltonRoom
{
public:
	std::string room_type;
	int available;
	double price_per_night;
	std::string date_from;
	std::string date_to;
};

class HiltonHotelAPI
{
public:
	static std::vector<HiltonRoom> SearchRooms(std::string city, std::string from_date, std::string to_date, int adults, int children, int needed_rooms)
	{
		std::vector<HiltonRoom> rooms;

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
	std::string room_type;
	int available;
	double price_per_night;
	std::string date_from;
	std::string date_to;
};

class MarriottHotelAPI
{
public:
	static std::vector<MarriottFoundRoom> FindRooms(std::string from_date, std::string to_date, std::string city, int needed_rooms, int adults, int children)
	{
		std::vector<MarriottFoundRoom> rooms;

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
