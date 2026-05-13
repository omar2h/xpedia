#pragma once

#include "itinerary_item.hpp"
class Flight : public ItineraryItem
{
    std::string airline{};
    std::string date{};
    double totalCost{};

public:
    const std::string &getAirline() const { return airline; }
    void setAirline(const std::string &airline_) { airline = airline_; }

    const std::string &getDate() const { return date; }
    void setDate(const std::string &date_) { date = date_; }

    [[nodiscard]] double getTotalCost() const { return totalCost; }
    void setTotalCost(double totalCost_) { totalCost = totalCost_; }

    [[nodiscard]] std::unique_ptr<ItineraryItem> clone() const override { return std::make_unique<Flight>(*this); }

    ~Flight() override = default;
};
