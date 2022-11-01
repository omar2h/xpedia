#ifndef __FLIGHT_H__
#define __FLIGHT_H__
#include "itineraryItem.h"
#include <iostream>
class Flight : public ItineraryItem
{
    std::string airline{};
    std::string date{};
    double totalCost{};

public:
    std::string getAirline() const { return airline; }
    void setAirline(const std::string &airline_) { airline = airline_; }

    std::string getDate() const { return date; }
    void setDate(const std::string &date_) { date = date_; }

    double getTotalCost() const { return totalCost; }
    void setTotalCost(double totalCost_) { totalCost = totalCost_; }

    std::string toString() const override;
    ItineraryItem *Clone() override { return new Flight(*this); }

    ~Flight() override
    {
        std::cout << "flight destructor\n";
    }
};

#endif // __FLIGHT_H__