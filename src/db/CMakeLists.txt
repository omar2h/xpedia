add_library(db)

target_sources(db
    PRIVATE
        customer_repository.cpp
        database.cpp
        id_generator.cpp
        user_repository.cpp
        repositories/itinerary_repository.cpp
        storage/file_storage.cpp
        mappers/itinerary_mapper.cpp

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