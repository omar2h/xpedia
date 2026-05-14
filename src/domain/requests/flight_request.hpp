#pragma once

#include "reservation_request.hpp"
#include <memory>
#include <string>

class FlightRequest : public ReservationRequest
{
    std::string fromCity{};
    std::string toCity{};
    std::string date{};
    int adults{};
    int children{};

public:
    FlightRequest() = default;
    FlightRequest(const std::string &, const std::string &, const std::string &, int, int);

    [[nodiscard]] std::unique_ptr<ReservationRequest> clone() override;

    [[nodiscard]] int getAdults() const { return adults; }
    void setAdults(int adults_) { adults = adults_; }

    [[nodiscard]] int getChildren() const { return children; }
    void setChildren(int children_) { children = children_; }

    [[nodiscard]] std::string getFromCity() const { return fromCity; }
    void setFromCity(const std::string &fromCity_) { fromCity = fromCity_; }

    [[nodiscard]] std::string getToCity() const { return toCity; }
    void setToCity(const std::string &toCity_) { toCity = toCity_; }

    [[nodiscard]] std::string getDate() const { return date; }
    void setDate(const std::string &date_) { date = date_; }

    [[nodiscard]] std::string toString() const override;

    ~FlightRequest() override = default;
};
