#pragma once

#include <memory>

#include "application/use_cases/search/search_hotels_use_case.hpp"

#include "presentation/presenters/hotel_search_presenter.hpp"

#include "infrastructure/hotel/aggregated/aggregated_hotel_search_service.hpp"

class IView;
class IInput;

struct HotelModule
{
    std::unique_ptr<AggregatedHotelSearchService> service;
    std::unique_ptr<SearchHotelsUseCase> useCase;
    std::unique_ptr<HotelSearchPresenter> presenter;
};

HotelModule createHotelModule(IView& view, IInput& input);
