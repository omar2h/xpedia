#include "hotel_search_provider_factory.hpp"

#include "../../application/providers/hotel_search_provider.hpp"

void HotelSearchProviderFactory::registerProvider(
    std::string id,
    std::string displayName,
    Creator creator)
{
    registry_.push_back({{std::move(id), std::move(displayName)},
                         std::move(creator)});
}

std::unique_ptr<HotelSearchProvider>
HotelSearchProviderFactory::create(
    const std::string &id) const
{
    for (const auto &entry : registry_)
    {
        if (entry.descriptor.id == id)
        {
            return entry.creator();
        }
    }

    return nullptr;
}

std::vector<std::unique_ptr<HotelSearchProvider>>
HotelSearchProviderFactory::createAll() const
{
    std::vector<std::unique_ptr<HotelSearchProvider>>
        providers;

    for (const auto &entry : registry_)
    {
        providers.push_back(
            entry.creator());
    }

    return providers;
}

std::vector<HotelSearchProviderDescriptor>
HotelSearchProviderFactory::getAvailableProviders() const
{
    std::vector<HotelSearchProviderDescriptor>
        descriptors;

    for (const auto &entry : registry_)
    {
        descriptors.push_back(
            entry.descriptor);
    }

    return descriptors;
}