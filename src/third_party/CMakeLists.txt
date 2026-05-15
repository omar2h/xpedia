# Downloads sqlite3 amalgamation and builds it as a static library

include(FetchContent)
FetchContent_Declare(
    sqlite3
    URL https://www.sqlite.org/2025/sqlite-amalgamation-3490100.zip
    SOURCE_DIR "${CMAKE_BINARY_DIR}/sqlite3-src"
    BINARY_DIR "${CMAKE_BINARY_DIR}/sqlite3-build"
)
FetchContent_MakeAvailable(sqlite3)

add_library(sqlite3 STATIC "${sqlite3_SOURCE_DIR}/sqlite3.c")

target_include_directories(sqlite3 PUBLIC "${sqlite3_SOURCE_DIR}")

# Suppress warnings in sqlite3 C code when compiled as C++
if(MSVC)
    target_compile_options(sqlite3 PRIVATE /W0)
else()
    target_compile_options(sqlite3 PRIVATE -w)
endif()

# Download and build libcurl for HTTP requests
# On Windows, you may need to install curl via vcpkg or set CURL_ROOT
find_package(CURL QUIET)
if(NOT CURL_FOUND)
    # Try to find curl in common locations or use vcpkg
    message(STATUS "CURL not found. You may need to install it via vcpkg: vcpkg install curl")
endif()
