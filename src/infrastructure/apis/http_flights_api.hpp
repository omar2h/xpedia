#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "http_client.hpp"
#include "../../third_party/json.hpp"

// HTTP-based flight API client
// This replaces the mock implementations with real HTTP calls

struct FlightSearchParams
{
    std::string from;
    std::string to;
    std::string date;
    int adults = 1;
    int children = 0;
};

struct FlightResult
{
    double price;
    std::string date;
    std::string airline;
    std::string flightNumber;
    std::string departureTime;
    std::string arrivalTime;
    std::string fromAirport;
    std::string toAirport;
};

struct FlightReservationParams
{
    std::string flightId;
    std::string passengerName;
    std::string passengerEmail;
    std::string passengerPhone;
};

class HttpFlightsAPI
{
public:
    explicit HttpFlightsAPI(std::string baseUrl, std::string apiKey = "")
        : m_baseUrl(std::move(baseUrl)), m_apiKey(std::move(apiKey)), m_httpClient(HttpClient::create()) {}

    std::vector<FlightResult> searchFlights(const FlightSearchParams &params);
    std::optional<std::string> reserveFlight(const FlightReservationParams &params);

private:
    std::string m_baseUrl;
    std::string m_apiKey;
    std::unique_ptr<HttpClient> m_httpClient;

    std::string buildUrl(const std::string &endpoint, const std::map<std::string, std::string> &params);
    std::map<std::string, std::string> buildHeaders();
};

// British Airways HTTP API
class BritishAirwaysHttpAPI
{
public:
    static std::vector<FlightResult> searchFlights(const FlightSearchParams &params);
    static std::optional<std::string> reserveFlight(const FlightReservationParams &params);
};

// Air France HTTP API
class AirFranceHttpAPI
{
public:
    static std::vector<FlightResult> searchFlights(const FlightSearchParams &params);
    static std::optional<std::string> reserveFlight(const FlightReservationParams &params);
};