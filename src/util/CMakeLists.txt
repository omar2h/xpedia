add_library(util STATIC
    id_generator.cpp
    password_utils.cpp
    env_loader.cpp
)

target_include_directories(util
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(util PUBLIC cxx_std_17)
