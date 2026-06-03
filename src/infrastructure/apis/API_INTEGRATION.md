# API Integration Guide

## Architecture Principle

**Flight booking offers** are fetched from a single real API — Duffel.
There is no separate "flight status" layer; Duffel is a booking API and
returns everything needed to display and select a flight.

```
Presentation
    ↓
Application Services
    ↓
Domain Models
    ↓
Infrastructure
    ├── DuffelFlightsAPI   ← real  (Duffel /air/offer_requests)
    ├── MockBookingAPI     ← mock  (fallback / pricing)
    ├── HTTP Client
    └── Persistence
```

---

## Layer Responsibilities

| Layer              | Status  | What it does                                   |
|--------------------|---------|------------------------------------------------|
| **Flight Booking** | **Real**| Offers, prices, routes, times — via Duffel     |
| **Booking / Offer**| Mock    | Fallback offers + pricing (MockBookingAPI)     |
| **Reservation**    | Mock    | Internal store (SQLite / JSON / in-memory)     |
| **Payment**        | Mock    | Always returns success                         |
| **Hotel**          | Mock    | `hilton_hotels_api.hpp` stubs                  |

---

## Directory Layout

```
src/infrastructure/
├── http/
│   ├── http_client.hpp          – abstract HTTP client interface
│   └── cpr_http_client.cpp      – CPR-based real HTTP implementation
│
├── apis/
│   └── flights/
│       ├── flight_offer_models.hpp   – FlightOffer, FlightSearchParams (lean booking structs)
│       ├── duffel_flights_api.hpp    – DuffelFlightsAPI (real booking API)
│       ├── duffel_flights_api.cpp    – Real HTTP implementation
│       └── mock_booking_api.hpp      – MockBookingAPI (fallback offers + pricing)
│
├── apis/  (legacy mock files, still used by other providers)
│   ├── expedia_flights_api.hpp   – Mock flight data
│   ├── expedia_hotels_api.hpp    – Mock hotel data
│   └── expedia_payments_api.hpp  – Mock payment data
│
└── config/
    └── api_config.hpp            – API URLs and environment-variable helpers
```

---

## Flight Booking — Real API (Duffel)

### `FlightOffer`  ([`flight_offer_models.hpp`](src/infrastructure/apis/flights/flight_offer_models.hpp))

A **lean booking offer** — what the user sees and selects.

```cpp
struct FlightOffer
{
    std::string id;
    std::string airline;
    std::string flightNumber;
    std::string from;          // IATA code
    std::string to;            // IATA code
    std::string departureTime;
    std::string arrivalTime;
    double      price    = 0.0;
    std::string currency = "USD";
};
```

### `FlightSearchParams`  ([`flight_offer_models.hpp`](src/infrastructure/apis/flights/flight_offer_models.hpp))

Minimal search parameters for a booking query.

```cpp
struct FlightSearchParams
{
    std::string from;
    std::string to;
    std::string departureDate;
    int         adults = 1;
};
```

### `DuffelFlightsAPI`  ([`duffel_flights_api.hpp`](src/infrastructure/apis/flights/duffel_flights_api.hpp))

Real HTTP client that calls the Duffel offer-request endpoint.

```cpp
std::vector<FlightOffer> DuffelFlightsAPI::searchFlights(const FlightSearchParams &params);
```

**Endpoint:** `POST https://api.duffel.com/air/offer_requests`

**Headers:**
| Header           | Value                    |
|------------------|--------------------------|
| `Authorization`  | `Bearer <api_key>`       |
| `Duffel-Version` | `v2`                     |
| `Content-Type`   | `application/json`       |

**Request body:**
```json
{
  "data": {
    "slices": [
      {
        "origin": "JFK",
        "destination": "LHR",
        "departure_date": "2026-05-20"
      }
    ],
    "passengers": [
      { "type": "adult" }
    ],
    "cabin_class": "economy"
  }
}
```

**Response — offers are at `data.offers[]`:**
```json
{
  "data": {
    "offers": [
      {
        "id": "off_123",
        "owner": { "name": "British Airways" },
        "total_amount": "234.50",
        "total_currency": "GBP",
        "slices": [
          {
            "origin": { "iata_code": "JFK" },
            "destination": { "iata_code": "LHR" },
            "departure_at": "2026-05-20T18:30:00+00:00",
            "arrival_at":   "2026-05-21T06:30:00+00:00"
          }
        ]
      }
    ]
  }
}
```

---

## Mock Booking / Pricing — Fallback Layer

### `MockBookingAPI`  ([`mock_booking_api.hpp`](src/infrastructure/apis/flights/mock_booking_api.hpp))

Returns hardcoded `FlightOffer` objects.  No network call.  Used as a
fallback when the real Duffel API is unavailable.

```cpp
std::vector<FlightOffer> MockBookingAPI::searchOffers(from, to, date, adults, children);
```

---

## How Providers Use the Duffel Layer

Each flight provider calls `DuffelFlightsAPI::searchFlights()` and maps
the result into domain `Flight` entities:

```cpp
DuffelFlightsAPI duffel(apiKey);
FlightSearchParams params{from, to, date, adults};

std::vector<FlightOffer> offers = duffel.searchFlights(params);

for (const auto &offer : offers)
{
    Flight flight;
    flight.setAirline(offer.airline);
    flight.setFlightNumber(offer.flightNumber);
    flight.setFrom(offer.from);
    flight.setTo(offer.to);
    flight.setDate(offer.departureTime);
    flight.setTotalCost(offer.price);
    results.push_back(flight.clone());
}
```

---

## Reservation Layer — Internal Only

`reserve()` on each provider is a **mock stub**.  It does not call any
external booking API.  In a real system this would write to a local
persistence store (SQLite / JSON / in-memory) via `ReservationService`.

```cpp
bool Provider::reserve(Reservation *) const
{
    return MockBookingAPI::reserve("mock_offer_id");
}
```

---

## Payments — Mock Layer

`StripePaymentStrategy`, `PayPalPaymentStrategy`, and `SquarePaymentStrategy`
all delegate to [`expedia_payments_api.hpp`](src/infrastructure/apis/expedia_payments_api.hpp),
which always returns `true`.  No real payment gateway is called.

---

## Environment Variables

```cmd
set DUFFEL_API_KEY=your_key
```

Read via `ApiConfig::getEnvVar()` in [`api_config.hpp`](src/infrastructure/config/api_config.hpp).

---

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Requires the **CPR** library (for `CprHttpClient`) and **nlohmann/json**
(vendored at `src/third_party/json.hpp`).
