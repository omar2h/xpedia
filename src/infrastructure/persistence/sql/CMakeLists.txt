add_library(db_sql
    sql_database.cpp
)

target_link_libraries(db_sql
    PUBLIC
        db
        infrastructure
        sqlite3
)

target_include_directories(db_sql
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(db_sql PUBLIC cxx_std_17)
