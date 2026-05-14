add_library(domain)

target_sources(domain
    PRIVATE
        entities/customer.cpp
        entities/flight.cpp
        entities/flight_reservation.cpp
        entities/hotel_reservation.cpp
        entities/hotel_room.cpp
        entities/itinerary.cpp
        entities/itinerary_item.cpp
        entities/user.cpp
        factories/reservation_factory.cpp
        requests/flight_request.cpp
        requests/hotel_request.cpp
)

target_include_directories(domain
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(domain PUBLIC cxx_std_17)
