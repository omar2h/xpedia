#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

class BookingProvider;

struct BookingProviderDescriptor
{
    std::string id;
    std::string displayName;
};

class BookingProviderFactory
{
public:
    using Creator = std::function<std::unique_ptr<BookingProvider>()>;

    void registerProvider(std::string id, std::string displayName, Creator creator);

    [[nodiscard]] std::unique_ptr<BookingProvider> create(const std::string &id) const;

private:
    struct Entry
    {
        BookingProviderDescriptor descriptor;
        Creator creator;
    };

    std::vector<Entry> registry_;
};