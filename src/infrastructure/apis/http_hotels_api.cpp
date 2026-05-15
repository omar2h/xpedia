#include "http_hotels_api.hpp"
#include <iostream>

using json = nlohmann::json;

// HttpHotelsAPI implementation
std::string HttpHotelsAPI::buildUrl(const std::string &endpoint, const std::map<std::string, std::string> &params)
{
    std::string url = m_baseUrl + endpoint;

    if (!params.empty())
    {
        url += "?";
        bool first = true;
        for (const auto &[key, value] : params)
        {
            if (!first)
                url += "&";
            url += key + "=" + value;
            first = false;
        }
    }

    return url;
}

std::map<std::string, std::string> HttpHotelsAPI::buildHeaders()
{
    std::map<std::string, std::string> headers{
        {"Accept", "application/json"},
        {"Content-Type", "application/json"}};

    if (!m_apiKey.empty())
    {
        headers["Authorization"] = "Bearer " + m_apiKey;
    }

    return headers;
}

std::vector<HotelRoomResult> HttpHotelsAPI::searchRooms(const HotelSearchParams &params)
{
    std::vector<HotelRoomResult> results;

    std::map<std::string, std::string> queryParams{
        {"city", params.city},
        {"fromDate", params.fromDate},
        {"toDate", params.toDate},
        {"adults", std::to_string(params.adults)},
        {"children", std::to_string(params.children)},
        {"rooms", std::to_string(params.rooms)}};

    std::string url = buildUrl("/hotels/search", queryParams);
    std::string response = m_httpClient->get(url, buildHeaders());

    try
    {
        auto j = json::parse(response);
        for (const auto &item : j["rooms"])
        {
            HotelRoomResult result;
            result.roomType = item["roomType"].get<std::string>();
            result.available = item["available"].get<int>();
            result.pricePerNight = item["pricePerNight"].get<double>();
            result.dateFrom = item["dateFrom"].get<std::string>();
            result.dateTo = item["dateTo"].get<std::string>();
            result.hotelName = item["hotelName"].get<std::string>();
            result.hotelId = item["hotelId"].get<std::string>();
            results.push_back(result);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing hotel response: " << e.what() << std::endl;
    }

    return results;
}

std::optional<std::string> HttpHotelsAPI::reserveRoom(const HotelReservationParams &params)
{
    json body{
        {"roomId", params.roomId},
        {"guestName", params.guestName},
        {"guestEmail", params.guestEmail},
        {"guestPhone", params.guestPhone}};

    std::string url = buildUrl("/hotels/reserve", {});
    std::string response = m_httpClient->post(url, body.dump(), buildHeaders());

    try
    {
        auto j = json::parse(response);
        return j["reservationId"].get<std::string>();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing reservation response: " << e.what() << std::endl;
    }

    return std::nullopt;
}

// HiltonHttpAPI implementation
std::vector<HotelRoomResult> HiltonHttpAPI::searchRooms(const HotelSearchParams &params)
{
    HttpHotelsAPI api("https://api.hilton.com");
    return api.searchRooms(params);
}

std::optional<std::string> HiltonHttpAPI::reserveRoom(const HotelReservationParams &params)
{
    HttpHotelsAPI api("https://api.hilton.com");
    return api.reserveRoom(params);
}

// MarriottHttpAPI implementation
std::vector<HotelRoomResult> MarriottHttpAPI::searchRooms(const HotelSearchParams &params)
{
    HttpHotelsAPI api("https://api.marriott.com");
    return api.searchRooms(params);
}

std::optional<std::string> MarriottHttpAPI::reserveRoom(const HotelReservationParams &params)
{
    HttpHotelsAPI api("https://api.marriott.com");
    return api.reserveRoom(params);
}