#pragma once

namespace JsonKeys
{

// User fields
inline constexpr auto id = "id";
inline constexpr auto firstName = "firstName";
inline constexpr auto lastName = "lastName";
inline constexpr auto email = "email";
inline constexpr auto phone = "phone";
inline constexpr auto password = "password";

// Card fields
inline constexpr auto cards = "cards";
inline constexpr auto owner = "owner";
inline constexpr auto number = "number";
inline constexpr auto expiryDate = "expiry_date";
inline constexpr auto ccv = "ccv";

// Customer fields
inline constexpr auto itineraries = "itineraries";

// Itinerary fields
inline constexpr auto customerId = "customer_id";
inline constexpr auto reservations = "reservations";
inline constexpr auto cost = "cost";

// Reservation fields (flight)
inline constexpr auto type = "type";
inline constexpr auto requestType = "requestType";
inline constexpr auto airline = "airline";
inline constexpr auto from = "from";
inline constexpr auto to = "to";
inline constexpr auto date = "date";
inline constexpr auto adults = "adults";
inline constexpr auto children = "children";

// Reservation fields (hotel)
inline constexpr auto hotel = "hotel";
inline constexpr auto city = "city";
inline constexpr auto roomType = "room_type";
inline constexpr auto rooms = "rooms";

// Payment API fields (used by Square/PayPal/Stripe)
inline constexpr auto userInfo = "user_info";
inline constexpr auto cardInfo = "card_info";
inline constexpr auto paymentId = "ID";
inline constexpr auto paymentDate = "DATE";
inline constexpr auto paymentCcv = "CCV";
inline constexpr auto paymentMoney = "money";

} // namespace JsonKeys
