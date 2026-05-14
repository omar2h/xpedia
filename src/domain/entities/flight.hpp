#pragma once

#include "itinerary_item.hpp"
#include "../visitors/itinerary_item_visitor.hpp"

class Flight : public ItineraryItem
{
    std::string airline{};
    std::string date{};
    double totalCost{};

public:
    [[nodiscard]] const std::string &getAirline() const { return airline; }
    void setAirline(const std::string &airline_) { airline = airline_; }

    [[nodiscard]] const std::string &getDate() const { return date; }
    void setDate(const std::string &date_) { date = date_; }

    [[nodiscard]] double getTotalCost() const { return totalCost; }
    void setTotalCost(double totalCost_) { totalCost = totalCost_; }

    [[nodiscard]] std::unique_ptr<ItineraryItem> clone() const override { return std::make_unique<Flight>(*this); }

    void accept(ItineraryItemVisitor &visitor) const override { visitor.visit(*this); }

    ~Flight() override = default;
};
