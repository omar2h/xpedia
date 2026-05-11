add_library(model)

target_sources(model
    PRIVATE
        customer.cpp
        flight.cpp
        hotel_room.cpp
        itinerary.cpp
        itinerary_item.cpp
        payment_card.cpp
        user.cpp

        factories/reservation_factory.cpp
        factories/reservation_request_factory.cpp

        requests/flight_request.cpp
        requests/hotel_request.cpp

        reservations/flight_reservation.cpp
        reservations/hotel_reservation.cpp

        serializers/reservation_serializer.cpp
)

target_include_directories(model
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(model PUBLIC cxx_std_17)