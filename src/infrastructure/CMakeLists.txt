add_library(infrastructure)

target_sources(infrastructure
    PRIVATE
        factories/payment_factory.cpp

        factories/booking_provider_factory.cpp
        factories/hotel_search_provider_factory.cpp

        serialization/reservation_serializer.cpp

        # HTTP transport layer
        http/http_client.hpp
        http/cpr_http_client.cpp

        flight/aggregated/aggregated_flight_search_service.cpp

        # ── Flight APIs ──────────────────────────────────────────────────
        # Mock flight search service (for testing / offline mode)
        apis/flights/mock_flight_search_service.cpp

        # Mock booking API (offline route search)
        apis/flights/mock_booking_api.cpp

        # Duffel real API integration
        flight/duffel/client/duffel_client.cpp
        flight/duffel/parser/duffel_parser.cpp
        flight/duffel/mapper/duffel_mapper.cpp
        flight/duffel/duffel_flight_service.cpp

        # ── Hotel APIs ───────────────────────────────────────────────────
        # Real hotel API (not yet wired to providers)
        apis/hotels/hilton_hotels_api.cpp

        # ── Hotel Duffel Search ──────────────────────────────────────────
        hotel/aggregated/aggregated_hotel_search_service.cpp
        hotel/liteapi/client/liteapi_hotel_client.cpp
        hotel/liteapi/parser/liteapi_hotel_parser.cpp
        # hotel/liteapi/mapper/liteapi_hotel_mapper.cpp
        hotel/liteapi/liteapi_hotel_service.cpp
)

target_include_directories(infrastructure
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party
)

target_link_libraries(infrastructure
    PUBLIC
        application
        cpr::cpr
)

target_compile_features(infrastructure PUBLIC cxx_std_17)
