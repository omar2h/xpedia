#include "duffel_client.hpp"

#include <map>

DuffelClient::DuffelClient(const std::string &apiKey)
    : m_apiKey(apiKey),
      m_http(HttpClient::create())
{
}

Result<std::string> DuffelClient::searchFlights(const FlightSearchRequest &request)
{
    std::string body =
        R"({
            "data": {
                "slices": [
                    {
                        "origin": ")" +
        request.origin + R"(",
                        "destination": ")" +
        request.destination + R"(",
                        "departure_date": ")" +
        request.departureDate + R"("
                    }
                ],
                "passengers": [)";

    for (int i = 0; i < request.adults; ++i)
    {
        if (i > 0)
        {
            body += ",";
        }

        body += R"({ "type": "adult" })";
    }

    body += R"(],
                "cabin_class": "economy"
            }
        })";

    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer " + m_apiKey},
        {"Duffel-Version", "v2"},
        {"Content-Type", "application/json"}};

    auto response = m_http->post(
        "https://api.duffel.com/air/offer_requests",
        body,
        headers);

    if (response.empty())
    {
        return Result<std::string>::failure(
            "Duffel request failed");
    }

    return Result<std::string>::success(
        std::move(response));
}