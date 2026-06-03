#pragma once

#include <memory>
#include <string>

#include "../../../../domain/result.hpp"
#include "../../../../domain/value_objects/hotel_search_request.hpp"
#include "../../../http/http_client.hpp"

class LiteApiHotelClient
{
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_http;

  public:
    explicit LiteApiHotelClient(const std::string& apiKey);

    Result<std::string> searchHotels(const HotelSearchRequest& request);
};
