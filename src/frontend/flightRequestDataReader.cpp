#include "flightRequestDataReader.h"
#include <iostream>

ReservationRequest *FlightRequestDataReader::read()
{
    std::string from{};
    std::string to{};
    std::string date{};
    int adults{};
    int children{};

    std::cout << "Enter From City: ";
    std::cin >> from;
    std::cout << "Enter To City: ";
    std::cin >> to;
    std::cout << "Enter date: ";
    std::cin >> date;
    std::cout << "Enter number of adults and children: ";
    std::cin >> adults >> children;

    request->setFromCity(from);
    request->setToCity(to);
    request->setDate(date);
    request->setAdults(adults);
    request->setChildren(children);

    return request->Clone();
}
FlightRequestDataReader::FlightRequestDataReader()
{
    request = new FlightRequest;
}
