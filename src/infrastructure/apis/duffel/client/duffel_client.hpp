#pragma once

#include <memory>
#include <string>

#include "../../../http/http_client.hpp"

class DuffelClient
{
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_http;

public:
    explicit DuffelClient(const std::string &apiKey);

    std::string searchOffers(
        const std::string &from,
        const std::string &to,
        const std::string &date);
};
