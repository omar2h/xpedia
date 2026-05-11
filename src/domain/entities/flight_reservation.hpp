#pragma once

#include "reservation.hpp"
#include "flight.hpp"
#include <memory>

class FlightReservation : public Reservation
{
    std::unique_ptr<Flight> item{};
    std::string airline{};
    std::string from{};
    std::string to{};
    std::string date{};
    int adults{};
    int children{};
    double cost{};

public:
    FlightReservation() = default;
    FlightReservation(const FlightReservation &);
    FlightReservation &operator=(const FlightReservation &);
    FlightReservation(FlightReservation &&) noexcept = default;
    FlightReservation &operator=(FlightReservation &&) noexcept = default;
    ~FlightReservation() = default;

    [[nodiscard]] std::unique_ptr<Reservation> clone() const override;

    void accept(ReservationVisitor &) const override;

    [[nodiscard]] double totalCost() const override;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] std::string toSummaryString() const override;

    void setItem(const ItineraryItem &) override;

    // Setters for domain state
    void setFrom(const std::string &f) { from = f; }
    void setTo(const std::string &t) { to = t; }
    void setAdults(int a) { adults = a; }
    void setChildren(int c) { children = c; }
    void setAirline(const std::string &a) { airline = a; }
    void setDate(const std::string &d) { date = d; }
    void setCost(double c) { cost = c; }

    std::string getAirline() const { return airline; }
    std::string getFrom() const { return from; }
    std::string getTo() const { return to; }
    std::string getDate() const { return date; }
    int getAdults() const { return adults; }
    int getChildren() const { return children; }
};
