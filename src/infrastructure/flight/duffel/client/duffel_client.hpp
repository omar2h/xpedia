#pragma once

#include <memory>
#include <string>

#include "../../../../domain/value_objects/flight_search_request.hpp"
#include "../../../http/http_client.hpp"
#include "result.hpp"

class DuffelClient
{
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_http;

  public:
    explicit DuffelClient(const std::string& apiKey);

    Result<std::string> searchFlights(const FlightSearchRequest& request);
};
