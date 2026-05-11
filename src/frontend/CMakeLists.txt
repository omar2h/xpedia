add_library(frontend)

target_sources(frontend
    PRIVATE
        console_frontend.cpp
        input.cpp
        output.cpp
        login_handler.cpp
        signup_handler.cpp
)

target_include_directories(frontend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(frontend
    PUBLIC
        application
        domain
)

target_compile_features(frontend PUBLIC cxx_std_17)
