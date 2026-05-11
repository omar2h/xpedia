add_library(infrastructure)

target_sources(infrastructure
    PRIVATE
        factories/flights_manager_factory.cpp
        factories/hotels_manager_factory.cpp
        factories/itinerary_manager_factory.cpp
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
