#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "../http/http_client.hpp"
#include "../../third_party/json.hpp"
#include "hotel_models.hpp"

// Hilton Hotels API client
// This is the specific implementation for the Hilton hotel API provider

class HiltonHotelsAPI
{
public:
    explicit HiltonHotelsAPI(std::string baseUrl, std::string apiKey = "")
        : m_baseUrl(std::move(baseUrl)), m_apiKey(std::move(apiKey)), m_httpClient(HttpClient::create()) {}

    std::vector<HotelRoomResult> searchRooms(const HotelSearchParams &params);
    std::optional<std::string> reserveRoom(const HotelReservationParams &params);

private:
    std::string m_baseUrl;
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_httpClient;

    std::string buildUrl(const std::string &endpoint, const std::map<std::string, std::string> &params);
    std::map<std::string, std::string> buildHeaders();
};

// Marriott HTTP API (uses Hilton as backend)
class MarriottHttpAPI
{
public:
    static std::vector<HotelRoomResult> searchRooms(const HotelSearchParams &params);
    static std::optional<std::string> reserveRoom(const HotelReservationParams &params);
};