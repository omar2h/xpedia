#include "duffel_client.hpp"
#include <map>

DuffelClient::DuffelClient(const std::string &apiKey)
    : m_apiKey(apiKey)
    , m_http(HttpClient::create())
{
}

std::string DuffelClient::searchOffers(
    const std::string &from,
    const std::string &to,
    const std::string &date)
{
    std::string body = R"({
        "data": {
            "slices": [
                {
                    "origin": ")" + from + R"(",
                    "destination": ")" + to + R"(",
                    "departure_date": ")" + date + R"("
                }
            ],
            "passengers": [
                { "type": "adult" }
            ],
            "cabin_class": "economy"
        }
    })";

    std::map<std::string, std::string> headers;
    headers["Authorization"] = "Bearer " + m_apiKey;
    headers["Duffel-Version"] = "v2";
    headers["Content-Type"] = "application/json";

    return m_http->post("https://api.duffel.com/air/offer_requests", body, headers);
}
