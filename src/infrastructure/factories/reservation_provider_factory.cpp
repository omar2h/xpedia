#include "reservation_provider_factory.hpp"

#include "../../application/providers/reservation_provider.hpp"
#include "providers/british_airways_flight_provider.hpp"
#include "providers/air_france_flight_provider.hpp"
#include "providers/marriott_hotel_provider.hpp"
#include "providers/hilton_hotel_provider.hpp"

void ReservationProviderFactory::registerProvider(
    ReservationCategory category,
    std::string id,
    std::string displayName,
    Creator creator)
{
    registry_[category].push_back({{std::move(id), std::move(displayName), category}, std::move(creator)});
}

std::unique_ptr<ReservationProvider> ReservationProviderFactory::create(
    ReservationCategory category,
    const std::string &id) const
{
    auto catIt = registry_.find(category);
    if (catIt == registry_.end())
        return nullptr;

    for (const auto &entry : catIt->second)
    {
        if (entry.descriptor.id == id)
            return entry.creator();
    }
    return nullptr;
}

std::vector<std::unique_ptr<ReservationProvider>> ReservationProviderFactory::createAll(
    ReservationCategory category) const
{
    std::vector<std::unique_ptr<ReservationProvider>> providers;

    auto catIt = registry_.find(category);
    if (catIt == registry_.end())
        return providers;

    for (const auto &entry : catIt->second)
        providers.push_back(entry.creator());

    return providers;
}

std::vector<ProviderDescriptor> ReservationProviderFactory::getAvailableProviders() const
{
    std::vector<ProviderDescriptor> descriptors;

    for (const auto &[category, entries] : registry_)
        for (const auto &entry : entries)
            descriptors.push_back(entry.descriptor);

    return descriptors;
}
