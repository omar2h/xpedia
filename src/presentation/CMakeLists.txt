add_library(presentation)

target_sources(presentation
    PRIVATE
        console_frontend.cpp
        input.cpp
        output.cpp
        presenters/auth_presenter.cpp
        presenters/itinerary_presenter.cpp
        presenters/payment_presenter.cpp
        presenters/flight_search_presenter.cpp
        presenters/hotel_search_presenter.cpp
        forms/flight_search_form.cpp
        forms/hotel_search_form.cpp
        forms/card_input_form.cpp
        itinerary_item_flows/flight_itinerary_item_flow.cpp
        itinerary_item_flows/hotel_itinerary_item_flow.cpp
)

target_include_directories(presentation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(presentation
    PUBLIC
        application
        domain
    PRIVATE
        util
)

target_compile_features(presentation PUBLIC cxx_std_17)
