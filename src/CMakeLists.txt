cmake_minimum_required(VERSION 3.20)

project(
    TravelBookingSystem
    VERSION 1.0.0
    LANGUAGES C CXX
)

# ---- Global settings ----

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Options ----

option(ENABLE_WARNINGS "Enable compiler warnings" ON)
option(BUILD_TESTS "Build unit tests" ON)

# ---- Google Test (fetched at configure time) ----

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    include(FetchContent)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
set(CPR_USE_SYSTEM_CURL OFF)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5
)

FetchContent_MakeAvailable(cpr)

# ---- Subdirectories ----

add_subdirectory(third_party)
add_subdirectory(domain)
add_subdirectory(util)
add_subdirectory(infrastructure/persistence)
add_subdirectory(application)
add_subdirectory(infrastructure)
add_subdirectory(presentation)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# ---- Main executable ----

add_executable(travel_app app.cpp main.cpp)

target_link_libraries(travel_app
    PRIVATE
        presentation
        application
        infrastructure
        db_sql
        domain
        util
        sqlite3
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
