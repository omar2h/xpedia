#include "booking_provider_factory.hpp"

#include "../../application/providers/booking_provider.hpp"

void BookingProviderFactory::registerProvider(std::string id, std::string displayName, Creator creator)
{
    registry_.push_back({{std::move(id), std::move(displayName)}, std::move(creator)});
}

std::unique_ptr<BookingProvider> BookingProviderFactory::create(const std::string &id) const
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