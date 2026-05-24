#include "liteapi_hotel_client.hpp"

#include <algorithm>
#include <map>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

static std::string urlEncode(const std::string &s)
{
    std::string encoded;
    for (char c : s)
    {
        if (c == ' ')
            encoded += "%20";
        else
            encoded += c;
    }
    return encoded;
}

LiteApiHotelClient::LiteApiHotelClient(const std::string &apiKey)
    : m_apiKey(apiKey),
      m_http(HttpClient::create())
{
}

Result<std::string> LiteApiHotelClient::searchHotels(
    const HotelSearchRequest &request)
{
    std::map<std::string, std::string> geoHeaders{
        {"User-Agent", "TravelBookingSystem/1.0"},
        {"Accept", "application/json"}};

    std::string geoUrl =
        "https://nominatim.openstreetmap.org/search?q=" +
        urlEncode(request.city) + "&format=json&limit=1";

    auto geoResponse = m_http->get(geoUrl, geoHeaders);

    if (geoResponse.empty())
        return Result<std::string>::failure(
            "Geocoding request failed for city: " + request.city);

    json geoJson;

    try
    {
        geoJson = json::parse(geoResponse);
    }
    catch (const std::exception &e)
    {
        return Result<std::string>::failure(
            std::string("Invalid geocoding JSON: ") + e.what());
    }

    if (!geoJson.is_array() || geoJson.empty())
        return Result<std::string>::failure(
            "City not found: " + request.city);

    std::string lat = geoJson[0].value("lat", "");
    std::string lon = geoJson[0].value("lon", "");

    if (lat.empty() || lon.empty())
        return Result<std::string>::failure(
            "Could not determine coordinates for: " + request.city);

    std::map<std::string, std::string> headers{
        {"X-API-Key", m_apiKey},
        {"Accept", "application/json"},
        {"Content-Type", "application/json"}};

    std::string hotelsUrl =
        "https://api.liteapi.travel/v3.0/data/hotels?latitude=" +
        lat + "&longitude=" + lon;

    auto hotelsResponse = m_http->get(hotelsUrl, headers);

    if (hotelsResponse.empty())
        return Result<std::string>::failure("LiteAPI hotel search failed");

    json hotelsJson;

    try
    {
        hotelsJson = json::parse(hotelsResponse);
    }
    catch (const std::exception &e)
    {
        return Result<std::string>::failure(
            std::string("Invalid hotel list JSON: ") + e.what());
    }

    if (!hotelsJson.contains("data"))
        return Result<std::string>::failure("No hotels found");

    json hotelIds = json::array();

    for (const auto &hotel : hotelsJson["data"])
    {
        if (!hotel.contains("id"))
            continue;

        hotelIds.push_back(hotel["id"].get<std::string>());

        if (hotelIds.size() > 5)
            break;
    }

    if (hotelIds.empty())
        return Result<std::string>::failure("No hotel IDs found");

    json occupancies = json::array();

    json occupancy;

    occupancy["adults"] = request.adults;
    json children = json::array();
    std::cout << "child ages size: " << request.childAges.size() << std::endl;
    for (int i = 0; i < request.childAges.size(); ++i)
    {
        children.push_back(5);
    }
    occupancy["children"] = children;

    occupancies.push_back(occupancy);

    json ratesBody;

    ratesBody["hotelIds"] = hotelIds;
    ratesBody["occupancies"] = occupancies;
    ratesBody["guestNationality"] = "US";
    ratesBody["checkin"] = request.checkInDate;
    ratesBody["checkout"] = request.checkOutDate;
    ratesBody["currency"] = "USD";
    ratesBody["occupancies"] = occupancies;

    std::string ratesUrl = "https://api.liteapi.travel/v3.0/hotels/rates";

    auto ratesResponse = m_http->post(ratesUrl, ratesBody.dump(), headers);

    if (ratesResponse.empty())
        return Result<std::string>::failure("LiteAPI rates request failed");

    try
    {
        auto err = json::parse(ratesResponse);
        if (err.contains("status") && err["status"] == 400)
        {
            ratesBody["guestNationality"] = "US";

            ratesResponse = m_http->post(
                ratesUrl, ratesBody.dump(), headers);

            if (ratesResponse.empty())
                return Result<std::string>::failure(
                    "LiteAPI rates request failed (with guestNationality)");
        }
    }
    catch (...)
    {
    }

    return Result<std::string>::success(ratesResponse);
}
