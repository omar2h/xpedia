add_library(application)

target_sources(application
    PRIVATE
        services/auth_service.cpp
        services/reservation_service.cpp
        services/payment_service.cpp
        use_cases/create_itinerary_use_case.cpp
        use_cases/pay_itinerary_use_case.cpp
        use_cases/list_itineraries_use_case.cpp
        requests/flight_request.cpp
        requests/hotel_request.cpp
        factories/reservation_factory.cpp
        factories/reservation_request_factory.cpp
)

target_include_directories(application
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/apis
)

target_link_libraries(application
    PUBLIC
        domain
        db
    PRIVATE
        util
)

target_compile_features(application PUBLIC cxx_std_17)
