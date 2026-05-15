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

        # API implementations
        apis/flights/amadeus_flights_api.cpp
        apis/hotels/hilton_hotels_api.cpp
)

target_include_directories(infrastructure
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(infrastructure
    PUBLIC
        application
)

target_compile_features(infrastructure PUBLIC cxx_std_17)
