add_library(frontend)

target_sources(frontend
    PRIVATE
        console_frontend.cpp
        input_handler.cpp
        login_handler.cpp
        menu_printer.cpp
        printer.cpp
        signup_handler.cpp
)

target_include_directories(frontend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(frontend
    PUBLIC
        application
        model
)

target_compile_features(frontend PUBLIC cxx_std_17)