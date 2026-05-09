add_library(db)

target_sources(db
    PRIVATE
        customers_manager.cpp
        database.cpp
        id_generator.cpp
        itineraries_manager.cpp
        users_manager.cpp
)

target_include_directories(db
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(db
    PUBLIC
        model
)

target_compile_features(db PUBLIC cxx_std_17)