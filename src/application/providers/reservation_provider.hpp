#pragma once

#include <memory>
#include <vector>
class ItineraryItem;

class ReservationRequest;
class Reservation;

class ReservationProvider
{
    std::unique_ptr<ReservationRequest> request{};

public:
    ReservationProvider() = default;
    ReservationProvider(const ReservationProvider &other)
        : request(other.request ? other.request->clone() : nullptr) {}
    ReservationProvider &operator=(const ReservationProvider &other)
    {
        if (this != &other)
            request = other.request ? other.request->clone() : nullptr;
        return *this;
    }

    void setRequest(ReservationRequest *const request_)
    {
        request = request_->clone();
    }
    [[nodiscard]] virtual std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const = 0;

    [[nodiscard]] virtual bool reserve(Reservation *) const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] std::unique_ptr<ReservationRequest> getRequest() const
    {
        return request ? request->clone() : nullptr;
    }

    [[nodiscard]] virtual std::unique_ptr<ReservationProvider> clone() const = 0;

    virtual ~ReservationProvider() = default;
};
