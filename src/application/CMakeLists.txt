add_library(application)

target_sources(application
    PRIVATE
        application.cpp

        managers/air_france_flights_manager.cpp
        managers/british_airways_flights_manager.cpp
        managers/hilton_hotels_manager.cpp
        managers/marriott_hotels_manager.cpp
)

target_include_directories(application
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/apis
        ${PROJECT_SOURCE_DIR}/frontend
    PRIVATE
        ${PROJECT_SOURCE_DIR}/infrastructure
)

target_link_libraries(application
    PUBLIC
        model
        db
)

target_compile_features(application PUBLIC cxx_std_17)
