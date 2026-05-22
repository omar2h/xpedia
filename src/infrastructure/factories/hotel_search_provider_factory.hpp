#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

class HotelSearchProvider;

struct HotelSearchProviderDescriptor
{
    std::string id;
    std::string displayName;
};

class HotelSearchProviderFactory
{
public:
    using Creator =
        std::function<
            std::unique_ptr<HotelSearchProvider>()>;

    void registerProvider(
        std::string id,
        std::string displayName,
        Creator creator);

    [[nodiscard]]
    std::unique_ptr<HotelSearchProvider>
    create(const std::string &id) const;

    [[nodiscard]]
    std::vector<std::unique_ptr<HotelSearchProvider>>
    createAll() const;

    [[nodiscard]]
    std::vector<HotelSearchProviderDescriptor>
    getAvailableProviders() const;

private:
    struct Entry
    {
        HotelSearchProviderDescriptor descriptor;
        Creator creator;
    };

    std::vector<Entry> registry_;
};