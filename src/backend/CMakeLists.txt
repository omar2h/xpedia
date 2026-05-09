add_library(backend)

target_sources(backend
    PRIVATE
        backend.cpp

        factories/flights_manager_factory.cpp
        factories/hotels_manager_factory.cpp
        factories/itinerary_manager_factory.cpp
        factories/payment_factory.cpp

        managers/air_france_flights_manager.cpp
        managers/british_airways_flights_manager.cpp
        managers/hilton_hotels_manager.cpp
        managers/marriott_hotels_manager.cpp
)

target_include_directories(backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/apis
        ${PROJECT_SOURCE_DIR}/frontend
)

target_link_libraries(backend
    PUBLIC
        model
        db
)

target_compile_features(backend PUBLIC cxx_std_17)