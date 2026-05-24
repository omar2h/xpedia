#pragma once

#include <memory>
#include <string>

#include "../../../http/http_client.hpp"
#include "../../../../domain/result.hpp"
#include "../../../../domain/value_objects/hotel_search_request.hpp"

class DuffelHotelClient
{
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_http;

public:
    explicit DuffelHotelClient(const std::string &apiKey);

    Result<std::string> searchHotels(const HotelSearchRequest &request);
};
