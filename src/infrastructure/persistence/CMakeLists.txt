add_library(db)

target_sources(db
    PRIVATE
        database.cpp
        repositories/customer_repository.cpp
        repositories/user_repository.cpp
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
        domain
        infrastructure
        util
)

target_compile_features(db PUBLIC cxx_std_17)
