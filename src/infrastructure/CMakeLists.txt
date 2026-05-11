add_library(infrastructure)

target_sources(infrastructure
    PRIVATE
        factories/flight_provider_factory.cpp
        factories/hotel_provider_factory.cpp
        factories/reservation_provider_factory.cpp
        factories/payment_factory.cpp
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
