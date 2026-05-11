cmake_minimum_required(VERSION 3.20)

project(
    TravelBookingSystem
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---- Global settings ----

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Options ----

option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# ---- Subdirectories ----

add_subdirectory(domain)
add_subdirectory(util)
add_subdirectory(db)
add_subdirectory(application)
add_subdirectory(infrastructure)
add_subdirectory(frontend)

# ---- Main executable ----

add_executable(travel_app app.cpp)

target_link_libraries(travel_app
    PRIVATE
        frontend
        application
        infrastructure
        db
        domain
        util
)

target_include_directories(travel_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ---- Warnings helper ----

if(ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(travel_app PRIVATE /W4)
    else()
        target_compile_options(travel_app PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
