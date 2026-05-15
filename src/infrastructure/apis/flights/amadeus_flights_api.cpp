#include "amadeus_flights_api.hpp"
#include <iostream>
#include <sstream>

using json = nlohmann::json;

// AmadeusFlightsAPI implementation
std::string AmadeusFlightsAPI::buildUrl(const std::string &endpoint, const std::map<std::string, std::string> &params)
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

std::map<std::string, std::string> AmadeusFlightsAPI::buildHeaders()
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

std::vector<FlightResult> AmadeusFlightsAPI::searchFlights(const FlightSearchParams &params)
{
    std::vector<FlightResult> results;

    std::map<std::string, std::string> queryParams{
        {"from", params.from},
        {"to", params.to},
        {"date", params.date},
        {"adults", std::to_string(params.adults)},
        {"children", std::to_string(params.children)}};

    std::string url = buildUrl("/flights/search", queryParams);
    std::string response = m_httpClient->get(url, buildHeaders());

    try
    {
        auto j = json::parse(response);
        for (const auto &item : j["flights"])
        {
            FlightResult result;
            result.price = item["price"].get<double>();
            result.date = item["date"].get<std::string>();
            result.airline = item["airline"].get<std::string>();
            result.flightNumber = item["flightNumber"].get<std::string>();
            result.departureTime = item["departureTime"].get<std::string>();
            result.arrivalTime = item["arrivalTime"].get<std::string>();
            result.fromAirport = item["fromAirport"].get<std::string>();
            result.toAirport = item["toAirport"].get<std::string>();
            results.push_back(result);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing flight response: " << e.what() << std::endl;
    }

    return results;
}

std::optional<std::string> AmadeusFlightsAPI::reserveFlight(const FlightReservationParams &params)
{
    json body{
        {"flightId", params.flightId},
        {"passengerName", params.passengerName},
        {"passengerEmail", params.passengerEmail},
        {"passengerPhone", params.passengerPhone}};

    std::string url = buildUrl("/flights/reserve", {});
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

// BritishAirwaysHttpAPI implementation
std::vector<FlightResult> BritishAirwaysHttpAPI::searchFlights(const FlightSearchParams &params)
{
    AmadeusFlightsAPI api("https://api.britishairways.com");
    return api.searchFlights(params);
}

std::optional<std::string> BritishAirwaysHttpAPI::reserveFlight(const FlightReservationParams &params)
{
    AmadeusFlightsAPI api("https://api.britishairways.com");
    return api.reserveFlight(params);
}

// AirFranceHttpAPI implementation
std::vector<FlightResult> AirFranceHttpAPI::searchFlights(const FlightSearchParams &params)
{
    AmadeusFlightsAPI api("https://api.airfrance.com");
    return api.searchFlights(params);
}

std::optional<std::string> AirFranceHttpAPI::reserveFlight(const FlightReservationParams &params)
{
    AmadeusFlightsAPI api("https://api.airfrance.com");
    return api.reserveFlight(params);
}