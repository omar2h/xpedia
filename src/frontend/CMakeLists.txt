add_library(frontend)

target_sources(frontend
    PRIVATE
        console_frontend.cpp
        flight_request_data_reader.cpp
        frontend.cpp
        hotel_request_data_reader.cpp
        input_handler.cpp
        login_handler.cpp
        menu_printer.cpp
        printer.cpp
        request_data_reader.cpp
        signup_handler.cpp
)

target_include_directories(frontend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(frontend
    PUBLIC
        backend
        model
)

target_compile_features(frontend PUBLIC cxx_std_17)