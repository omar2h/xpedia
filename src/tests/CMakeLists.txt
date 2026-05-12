add_executable(run_tests
    test_reservation_factory.cpp
    test_reservation_serializer.cpp
    test_reservation_service.cpp
    test_payment_processor.cpp
    test_create_itinerary.cpp
)

target_link_libraries(run_tests
    PRIVATE
        application
        infrastructure
        domain
        util
        GTest::gtest
        GTest::gtest_main
)

target_include_directories(run_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_features(run_tests PUBLIC cxx_std_17)

include(GoogleTest)
gtest_discover_tests(run_tests)
