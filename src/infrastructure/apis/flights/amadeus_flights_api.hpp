#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "../http/http_client.hpp"
#include "../../third_party/json.hpp"
#include "flight_models.hpp"

// Amadeus Flights API client
// This is the specific implementation for the Amadeus travel API provider

class AmadeusFlightsAPI
{
public:
    explicit AmadeusFlightsAPI(std::string baseUrl, std::string apiKey = "")
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

// British Airways HTTP API (uses Amadeus as backend)
class BritishAirwaysHttpAPI
{
public:
    static std::vector<FlightResult> searchFlights(const FlightSearchParams &params);
    static std::optional<std::string> reserveFlight(const FlightReservationParams &params);
};

// Air France HTTP API (uses Amadeus as backend)
class AirFranceHttpAPI
{
public:
    static std::vector<FlightResult> searchFlights(const FlightSearchParams &params);
    static std::optional<std::string> reserveFlight(const FlightReservationParams &params);
};