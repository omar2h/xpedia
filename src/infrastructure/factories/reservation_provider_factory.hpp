#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../domain/entities/reservation_category.hpp"

class ReservationProvider;

struct ProviderDescriptor
{
    std::string id;
    std::string displayName;
    ReservationCategory category;
};

class ReservationProviderFactory
{
public:
    using Creator = std::function<std::unique_ptr<ReservationProvider>()>;

    void registerProvider(
        ReservationCategory category,
        std::string id,
        std::string displayName,
        Creator creator);

    [[nodiscard]] std::unique_ptr<ReservationProvider> create(
        ReservationCategory category,
        const std::string &id) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> createAll(
        ReservationCategory category) const;

    [[nodiscard]] std::vector<ProviderDescriptor> getAvailableProviders() const;

private:
    struct Entry
    {
        ProviderDescriptor descriptor;
        Creator creator;
    };

    std::unordered_map<ReservationCategory, std::vector<Entry>> registry_;
};
