#pragma once

#include "reservation.hpp"

#include "../entities/flight.hpp"
#include "../value_objects/flight_search_request.hpp"

class FlightReservation : public Reservation
{
    Flight flight;

    std::string from;
    std::string to;

    int adults{};
    int children{};

    double cost{};

    bool hasFlight{};

    void recalculateCost();

  public:
    [[nodiscard]] const std::string& getAirline() const
    {
        return flight.getAirline();
    }
    void setAirline(const std::string& airline)
    {
        flight.setAirline(airline);
    }

    [[nodiscard]] const std::string& getFlightNumber() const
    {
        return flight.getFlightNumber();
    }
    void setFlightNumber(const std::string& flightNumber)
    {
        flight.setFlightNumber(flightNumber);
    }

    [[nodiscard]] const std::string& getFrom() const
    {
        return from;
    }
    void setFrom(const std::string& from_)
    {
        from = from_;
    }

    [[nodiscard]] const std::string& getTo() const
    {
        return to;
    }
    void setTo(const std::string& to_)
    {
        to = to_;
    }

    [[nodiscard]] const std::string& getDate() const
    {
        return flight.getDate();
    }
    void setDate(const std::string& date)
    {
        flight.setDate(date);
    }

    [[nodiscard]] int getAdults() const
    {
        return adults;
    }
    void setAdults(int adults_)
    {
        adults = adults_;
    }

    [[nodiscard]] int getChildren() const
    {
        return children;
    }
    void setChildren(int children_)
    {
        children = children_;
    }

    void setCost(double cost_)
    {
        cost = cost_;
    }

    [[nodiscard]] std::unique_ptr<Reservation> clone() const override;

    [[nodiscard]] double totalCost() const override;

    void accept(ReservationVisitor& visitor) const override;

    void setItem(const ItineraryItem& item) override;

    void applySearchRequest(const FlightSearchRequest& request);
};
