add_library(infrastructure)

target_sources(infrastructure
    PRIVATE
        factories/reservation_provider_factory.cpp
        factories/payment_factory.cpp

        providers/air_france_flight_provider.cpp
        providers/british_airways_flight_provider.cpp
        providers/hilton_hotel_provider.cpp
        providers/marriott_hotel_provider.cpp

        serialization/reservation_serializer.cpp

        # HTTP transport layer
        http/http_client.hpp
        http/cpr_http_client.cpp

        # ── Flight APIs ──────────────────────────────────────────────────
        # Mock flight search service (for testing / offline mode)
        apis/flights/mock_flight_search_service.cpp

        # Mock booking API (offline route search)
        apis/flights/mock_booking_api.cpp

        # Duffel real API integration
        apis/duffel/client/duffel_client.cpp
        apis/duffel/parser/duffel_parser.cpp
        apis/duffel/mapper/duffel_mapper.cpp
        apis/duffel/duffel_flight_service.cpp

        # ── Hotel APIs ───────────────────────────────────────────────────
        # Real hotel API (not yet wired to providers)
        apis/hotels/hilton_hotels_api.cpp
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
