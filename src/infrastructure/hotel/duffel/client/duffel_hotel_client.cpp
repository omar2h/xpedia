#include "duffel_hotel_client.hpp"

#include <map>
#include <sstream>
#include <iostream>

DuffelHotelClient::DuffelHotelClient(const std::string &apiKey)
    : m_apiKey(apiKey),
      m_http(HttpClient::create())
{
}

Result<std::string> DuffelHotelClient::searchHotels(
    const HotelSearchRequest &request)
{
    std::ostringstream body;

    body << R"({
        "data":{
    )";

    // dates
    body << R"(
        "check_in_date":")"
         << request.checkInDate
         << R"(",
    )";

    body << R"(
        "check_out_date":")"
         << request.checkOutDate
         << R"(",
    )";

    // location
    body << R"(
        "location":{
            "radius":5,
            "geographic_coordinates":{
                "longitude":)"
         << request.longitude
         << R"(,
                "latitude":)"
         << request.latitude
         << R"(
            }
        },
    )";

    // rooms
    body << R"(
        "rooms":[
    )";

    for (int roomIndex = 0; roomIndex < request.rooms; ++roomIndex)
    {
        if (roomIndex > 0)
            body << ",";

        body << R"({
            "guests":[
        )";

        bool firstGuest = true;

        // adults
        for (int i = 0; i < request.adults; ++i)
        {
            if (!firstGuest)
                body << ",";

            body << R"({"type":"adult"})";

            firstGuest = false;
        }

        // children
        for (int age : request.childAges)
        {
            if (!firstGuest)
                body << ",";

            body << R"({"type":"child","age":)"
                 << age
                 << "}";

            firstGuest = false;
        }

        body << R"(]
        })";
    }

    body << R"(
        ]
    )";

    // close data/root
    body << R"(
        }
    })";

    std::string jsonBody = body.str();

    std::cout << "\n===== DUFFEL REQUEST =====\n";
    std::cout << jsonBody << std::endl;

    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer " + m_apiKey},
        {"Duffel-Version", "v2"},
        {"Content-Type", "application/json"},
        {"Accept", "application/json"}};

    auto response = m_http->post(
        "https://api.duffel.com/stays/search",
        jsonBody,
        headers);

    std::cout << "\n===== DUFFEL RESPONSE =====\n";
    std::cout << response << std::endl;

    if (response.empty())
    {
        return Result<std::string>::failure(
            "Duffel hotel request failed");
    }

    // prevent JSON parser crash
    if (response[0] != '{')
    {
        return Result<std::string>::failure(
            "Duffel returned non-JSON response:\n" + response);
    }

    return Result<std::string>::success(
        std::move(response));
}