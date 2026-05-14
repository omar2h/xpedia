#pragma once

#include "reservation.hpp"
#include "flight.hpp"

class FlightReservation : public Reservation
{
    Flight flight;
    bool hasFlight{};
    std::string from{};
    std::string to{};
    int adults{};
    int children{};
    double cost{};

    void recalculateCost();

public:
    FlightReservation() = default;
    FlightReservation(const FlightReservation &) = default;
    FlightReservation &operator=(const FlightReservation &) = default;
    FlightReservation(FlightReservation &&) noexcept = default;
    FlightReservation &operator=(FlightReservation &&) noexcept = default;
    ~FlightReservation() = default;

    [[nodiscard]] std::unique_ptr<Reservation> clone() const override;

    void accept(ReservationVisitor &) const override;

    [[nodiscard]] double totalCost() const override;

    void setItem(const ItineraryItem &) override;

    void applyRequest(const ReservationRequest &) override;

    void setFrom(const std::string &f) { from = f; }
    void setTo(const std::string &t) { to = t; }
    void setAdults(int a) { adults = a; }
    void setChildren(int c) { children = c; }
    void setAirline(const std::string &a) { flight.setAirline(a); }
    void setDate(const std::string &d) { flight.setDate(d); }
    void setCost(double c) { cost = c; }

    [[nodiscard]] const std::string &getAirline() const { return flight.getAirline(); }
    [[nodiscard]] const std::string &getFrom() const { return from; }
    [[nodiscard]] const std::string &getTo() const { return to; }
    [[nodiscard]] const std::string &getDate() const { return flight.getDate(); }
    [[nodiscard]] int getAdults() const { return adults; }
    [[nodiscard]] int getChildren() const { return children; }
};
