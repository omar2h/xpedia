#include "hotelRequestDataReader.h"
#include <iostream>
ReservationRequest *HotelRequestDataReader::read()
{
    std::string from{};
    std::string to{};
    std::string city{};
    int rooms{};
    int adults{};
    int children{};
    std::cout << "Please Enter From Date: ";
    std::cin >> from;
    std::cout << "Please Enter To Date: ";
    std::cin >> to;
    std::cout << "Please Enter the city: ";
    std::cin >> city;
    std::cout << "Please Enter no. of adults and children: ";
    std::cin >> adults >> children;
    std::cout << "Please Enter no. of rooms: ";
    std::cin >> rooms;

    hotelRequest->setFromDate(from);
    hotelRequest->setToDate(to);
    hotelRequest->setCity(city);
    hotelRequest->setRooms(rooms);
    hotelRequest->setAdults(adults);
    hotelRequest->setChildren(children);

    return hotelRequest->Clone();
}

HotelRequestDataReader::HotelRequestDataReader()
{
    hotelRequest = new HotelRequest;
}