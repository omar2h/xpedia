add_library(composition)

target_sources(composition
    PRIVATE
        flight/flight_module.cpp
        hotel/hotel_module.cpp
        auth/auth_module.cpp
)

target_link_libraries(composition
    PUBLIC
        application
        presentation
        infrastructure
        db_sql
        util
)

target_include_directories(composition
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(composition PUBLIC cxx_std_17)
