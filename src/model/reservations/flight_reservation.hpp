#pragma once

#include "../reservation.hpp"
#include "../flight.hpp"
#include "../requests/flight_request.hpp"
#include <memory>
using json = nlohmann::json;

class FlightReservationData;

class FlightReservation : public Reservation
{
    std::unique_ptr<FlightRequest> request{};
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
    explicit FlightReservation(const FlightReservationData &data);
    FlightReservation &operator=(const FlightReservation &);
    FlightReservation(FlightReservation &&) noexcept = default;
    FlightReservation &operator=(FlightReservation &&) noexcept = default;
    ~FlightReservation() = default;

    std::unique_ptr<Reservation> clone() const override;

    double total_cost() const override;

    std::string toString() const override;

    std::string toString2() const override;

    void setRequest(std::unique_ptr<ReservationRequest>) override;

    void setItem(ItineraryItem *const) override;

    void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) override;

    std::string getAirline() const
    {
        return airline;
    }

    std::string getFrom() const
    {
        return from;
    }

    std::string getTo() const
    {
        return to;
    }

    std::string getDate() const
    {
        return date;
    }

    int getAdults() const
    {
        return adults;
    }

    int getChildren() const
    {
        return children;
    }
};
