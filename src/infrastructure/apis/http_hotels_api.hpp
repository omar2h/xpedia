#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "http_client.hpp"
#include "../../third_party/json.hpp"

// HTTP-based hotel API client

struct HotelSearchParams
{
    std::string city;
    std::string fromDate;
    std::string toDate;
    int adults = 1;
    int children = 0;
    int rooms = 1;
};

struct HotelRoomResult
{
    std::string roomType;
    int available;
    double pricePerNight;
    std::string dateFrom;
    std::string dateTo;
    std::string hotelName;
    std::string hotelId;
};

struct HotelReservationParams
{
    std::string roomId;
    std::string guestName;
    std::string guestEmail;
    std::string guestPhone;
};

class HttpHotelsAPI
{
public:
    explicit HttpHotelsAPI(std::string baseUrl, std::string apiKey = "")
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

// Hilton HTTP API
class HiltonHttpAPI
{
public:
    static std::vector<HotelRoomResult> searchRooms(const HotelSearchParams &params);
    static std::optional<std::string> reserveRoom(const HotelReservationParams &params);
};

// Marriott HTTP API
class MarriottHttpAPI
{
public:
    static std::vector<HotelRoomResult> searchRooms(const HotelSearchParams &params);
    static std::optional<std::string> reserveRoom(const HotelReservationParams &params);
};