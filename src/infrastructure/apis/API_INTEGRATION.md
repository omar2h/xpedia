# Real API Integration Guide

This document explains how to integrate real API calls into the Travel Booking System.

## Overview

The project currently uses mock API implementations that return hardcoded data. This guide shows how to replace them with real HTTP API calls.

## Files Created

### New HTTP API Files
- [`http_client.hpp`](http_client.hpp) - HTTP client interface (abstracts the HTTP backend)
- [`http_flights_api.hpp`](http_flights_api.hpp) - HTTP-based flight API client
- [`http_flights_api.cpp`](http_flights_api.cpp) - Implementation
- [`http_hotels_api.hpp`](http_hotels_api.hpp) - HTTP-based hotel API client
- [`http_hotels_api.cpp`](http_hotels_api.cpp) - Implementation
- [`api_config.hpp`](api_config.hpp) - API configuration and environment variable handling

## Architecture

The HTTP API system uses an abstract `HttpClient` interface that can be implemented with different backends:

1. **MockHttpClient** (default) - Returns mock responses for development
2. **LibcurlHttpClient** - Real HTTP implementation using libcurl (to be implemented)

## How to Use Real APIs

### 1. Implement a Real HTTP Client (Optional)

To use real HTTP calls, implement the `HttpClient` interface:

```cpp
// src/infrastructure/apis/libcurl_http_client.cpp
#include "http_client.hpp"
#include <curl/curl.h>

class LibcurlHttpClient : public HttpClient {
public:
    std::string get(const std::string& url, const std::map<std::string, std::string>& headers = {}) override {
        // Implement using libcurl
        // See http://curl.se/libcurl/c/libcurl-tutorial.html
    }
    
    std::string post(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers = {}) override {
        // Implement using libcurl
    }
};

std::unique_ptr<HttpClient> HttpClient::create() {
    return std::make_unique<LibcurlHttpClient>();
}
```

### 2. Set Environment Variables

Set the API keys as environment variables:

**Windows (Command Prompt):**
```cmd
set BRITISH_AIRWAYS_API_KEY=your_api_key_here
set AIR_FRANCE_API_KEY=your_api_key_here
set HILTON_API_KEY=your_api_key_here
set MARRIOTT_API_KEY=your_api_key_here
```

**Windows (PowerShell):**
```powershell
$env:BRITISH_AIRWAYS_API_KEY="your_api_key_here"
$env:AIR_FRANCE_API_KEY="your_api_key_here"
$env:HILTON_API_KEY="your_api_key_here"
$env:MARRIOTT_API_KEY="your_api_key_here"
```

**Linux/macOS:**
```bash
export BRITISH_AIRWAYS_API_KEY=your_api_key_here
export AIR_FRANCE_API_KEY=your_api_key_here
export HILTON_API_KEY=your_api_key_here
export MARRIOTT_API_KEY=your_api_key_here
```

### 3. Update Provider Implementations

To use the new HTTP APIs, update the provider files:

**For British Airways** ([`british_airways_flight_provider.cpp`](src/infrastructure/providers/british_airways_flight_provider.cpp)):

```cpp
#include "../apis/http_flights_api.hpp"

std::vector<std::unique_ptr<ItineraryItem>> BritishAirwaysFlightProvider::searchReservations() const
{
    auto req = getRequest();
    const FlightRequest &request = dynamic_cast<const FlightRequest &>(*req);
    
    FlightSearchParams params;
    params.from = request.getFromCity();
    params.to = request.getToCity();
    params.date = request.getDate();
    params.adults = request.getAdults();
    params.children = request.getChildren();
    
    std::vector<FlightResult> flights = BritishAirwaysHttpAPI::searchFlights(params);
    
    std::vector<std::unique_ptr<ItineraryItem>> results;
    for (const auto &flight_ : flights)
    {
        Flight flight;
        flight.setCategory(ReservationCategory::flight);
        flight.setProviderId("british_airways");
        flight.setRequestType(RequestType::flight);
        flight.setAirline(getName());
        flight.setDate(flight_.date);
        flight.setTotalCost(flight_.price);
        results.push_back(flight.clone());
    }
    return results;
}
```

**For Hilton Hotels** ([`hilton_hotel_provider.cpp`](src/infrastructure/providers/hilton_hotel_provider.cpp)):

```cpp
#include "../apis/http_hotels_api.hpp"

std::vector<std::unique_ptr<ItineraryItem>> HiltonHotelProvider::searchReservations() const
{
    auto reqPtr = getRequest();
    HotelRequest &req = dynamic_cast<HotelRequest &>(*reqPtr);
    
    HotelSearchParams params;
    params.city = req.getCity();
    params.fromDate = req.getFromDate();
    params.toDate = req.getToDate();
    params.adults = req.getAdults();
    params.children = req.getChildren();
    params.rooms = req.getRooms();
    
    std::vector<HotelRoomResult> rooms = HiltonHttpAPI::searchRooms(params);
    
    std::vector<std::unique_ptr<ItineraryItem>> results;
    for (const auto &room : rooms)
    {
        HotelRoom hRoom{};
        hRoom.setDateFrom(room.dateFrom);
        hRoom.setDateTo(room.dateTo);
        hRoom.setRequestType(RequestType::hotel);
        hRoom.setCategory(ReservationCategory::hotel);
        hRoom.setProviderId("hilton");
        hRoom.setAvailableRooms(room.available);
        hRoom.setPricePerNight(room.pricePerNight);
        hRoom.setRoomType(room.roomType);
        hRoom.setHotelName(getName());
        results.push_back(hRoom.clone());
    }
    return results;
}
```

## API Endpoints

The HTTP API classes expect the following JSON response formats:

### Flight Search Response
```json
{
  "flights": [
    {
      "price": 200.0,
      "date": "2023-05-01",
      "airline": "British Airways",
      "flightNumber": "BA123",
      "departureTime": "10:00",
      "arrivalTime": "12:00",
      "fromAirport": "LHR",
      "toAirport": "JFK"
    }
  ]
}
```

### Hotel Search Response
```json
{
  "rooms": [
    {
      "roomType": "Deluxe King",
      "available": 5,
      "pricePerNight": 250.0,
      "dateFrom": "2023-05-01",
      "dateTo": "2023-05-05",
      "hotelName": "Hilton Downtown",
      "hotelId": "hilton_123"
    }
  ]
}
```

### Reservation Response
```json
{
  "reservationId": "res_abc123",
  "status": "confirmed"
}
```

## Building the Project

After making changes, rebuild the project:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Testing

The HTTP API classes can be tested with mock servers or by using the actual API endpoints. For development, you can use tools like:

- [json-server](https://github.com/typicode/json-server) for mock REST APIs
- [WireMock](http://wiremock.org/) for HTTP mock server
- Postman Mock Server

## Error Handling

The HTTP API implementations include basic error handling:
- JSON parsing error handling
- Network error handling via the HttpClient interface

## Next Steps

1. Implement a real `HttpClient` using libcurl, cpr, or WinHTTP
2. Obtain API keys from the respective providers
3. Set up environment variables
4. Update the provider implementations to use the new HTTP APIs
5. Test with the actual API endpoints